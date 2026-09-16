/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Dio.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API implementations of Dio Driver Component.                                                    */
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
 * 2.4.1:  19/06/2025  : Remove SW-VERSION in header file
 * 2.4.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to for Ver22.01.02 U2Bx Beta2
 * 2.1.1:  11/06/2024  : As part of ARDAACL-37399, following changes are made
 *                       Remove Msg 3678 comment for declaration of LpPortAddress in Dio_FlipChannel
 *                       Add Analog register
 * 2.1.0:  29/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.1:  20/10/2023  : Remove Msg 2814, 2824, 2844
 *         16/10/2023  : Correct Syntax of Dio_MaskedWritePort API
 *         12/10/2023  : Update SW-VERSION 2.0.1
 * 2.0.0:  17/07/2023  : Add the implement to check invalid core to support multi-core.
 *                       Change macro function from DIO_INTERRUPT_CONTROL_PROTECTION to 
 *                       DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL to support multi core. 
 *         23/04/2023  : Update Description of Global Variables Used for APIs:Dio_ReadPort, Dio_WritePort,
 *                       Dio_ReadChannel, Dio_WriteChannel, Dio_FlipChannel, Dio_ReadChannelGroup,
 *                       Dio_WriteChannelGroup, Dio_MaskedWritePort, Dio_ReadChannelOutputValue,
 *                       Dio_ReadChannelGroupOutputValue.
 *                       Update name of parameters (In) and Description of Global Variables Used for
 *                       internal function Dio_SetPweMode.
 *                       As per ARDAACA-1265:
 *                       Update Return parameter description in APIs: Dio_ReadPort, Dio_ReadChannelGroup,
 *                       Dio_ReadChannelGroupOutputValue.
 * 1.4.2:  09/05/2022  : Removed "else" statement don't use when no action required 
 *         12/04/2022  : Update SW-Version 1.4.2 
 * 1.4.1:  06/12/2021  : Update SW-Version 1.4.1 
 * 1.4.0:  08/10/2021  : Remove LulPortModeLevel and check output mode (DIO_OUTPUT_MODE_PIN_EXISTENCE_CHECK)
 *                       in API: Dio_WritePort, Dio_WriteChannel, Dio_WriteChannelGroup for  
 *                       requirement Autosar and Dio_MaskedWritePort for requirement Renesas
 *                       Update SW-Version 1.4.0
 * 1.3.1:  08/07/2021  : Correct the If-Else statement in Dio_ReadPort () to determine the Dio Port type then using 
 *                       correct pointer access 8-bit for Jtag Port or 16-bit for Digital and Analog Port 
 *         02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         06/05/2021  : Add a space before and after a binary operator follow
 *                       rule Style_Format_009.
 *                       Composition of type: <Component name>_<Type name>Type
 *                       follow Name_Type_002: Dio_PortGroupType,
 *                       Dio_PortChannelType, Dio_PortDataType.
 *                       Change reserved bit to write value of PSR register
 *                       in 3 API: Dio_WritePort, Dio_MaskedWritePort
 *                       Dio_WriteChannelGroup.
 * 1.2.0:  26/08/2020  : Release
 * 1.1.1:  26/08/2020  : Update SW-VERSION
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.2:  22/05/2020  : Update software version definition.
 * 1.0.1:  19/03/2020  : Add Justification for QAC MISRA-C:2012
 * 1.0.0:  09/09/2019  : Initial Version.
*/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for macro definitions and API prototypes */
#include "Dio.h"
#if (DIO_DEV_ERROR_DETECT == STD_ON)
/* Included for declaration of the function Det_ReportError() */
#include "Det.h"
#endif
#if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Dio.h"
#endif

/* Include OS service */
#if (DIO_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define DIO_C_AR_RELEASE_MAJOR_VERSION    DIO_AR_RELEASE_MAJOR_VERSION_VALUE
#define DIO_C_AR_RELEASE_MINOR_VERSION    DIO_AR_RELEASE_MINOR_VERSION_VALUE
#define DIO_C_AR_RELEASE_REVISION_VERSION DIO_AR_RELEASE_REVISION_VERSION_VALUE

/* Software version information */
#define DIO_C_SW_MAJOR_VERSION            DIO_SW_MAJOR_VERSION_VALUE
#define DIO_C_SW_MINOR_VERSION            DIO_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (DIO_AR_RELEASE_MAJOR_VERSION != DIO_C_AR_RELEASE_MAJOR_VERSION)
  #error "Dio.c : Mismatch in Release Major Version"
#endif

#if (DIO_AR_RELEASE_MINOR_VERSION != DIO_C_AR_RELEASE_MINOR_VERSION)
  #error "Dio.c : Mismatch in Release Minor Version"
#endif

#if (DIO_AR_RELEASE_REVISION_VERSION != DIO_C_AR_RELEASE_REVISION_VERSION)
  #error "Dio.c : Mismatch in Release Revision Version"
#endif

#if (DIO_SW_MAJOR_VERSION != DIO_C_SW_MAJOR_VERSION)
  #error "Dio.c : Mismatch in Software Major Version"
#endif

#if (DIO_SW_MINOR_VERSION != DIO_C_SW_MINOR_VERSION)
  #error "Dio.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for improve safety by reducing the possibility that      */
/*                       the referenced data is unintentionally modified through an unexpected alias and improves     */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588,   */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0759)    : An object of union type has been defined.                                                    */
/* Rule                : MISRA C:2012 Rule-19.2, CWE Rule CWE-843                                                     */
/* JV-01 Justification : Data access of larger data types is used to achieve better throughput.                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.3, CWE Rule CWE-681, CWE-136, CWE-192                    */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define DIO_START_SEC_PRIVATE_CODE
#include "Dio_MemMap.h"

STATIC FUNC(void, DIO_PRIVATE_CODE) Dio_SetPweMode(const uint32 LulGroup, const uint8 LucMode);

#define DIO_STOP_SEC_PRIVATE_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Dio_ReadPort
**
** Service ID            : 0x02
**
** Description           : This service returns the level of all channels of
**                         given Port.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : PortId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Dio_PortLevelType
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : PPRn, JPPR0, APPRn
**
** Reference ID          : DIO_DUD_ACT_001, DIO_DUD_ACT_001_ERR001, DIO_DUD_ACT_001_ERR002
***********************************************************************************************************************/
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadPort(Dio_PortType PortId)                                              /* PRQA S 1503 # JV-01 */
{
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpPortAddress;                                                            /* PRQA S 3678 # JV-01 */
  Dio_PortLevelType LddPortLevel;

  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucDetErrFlag;

  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Initialize the return value to 0 */
  LddPortLevel = DIO_LOW_LEVEL_OUTPUT;
  #endif
  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  /* Check whether the Port Id is out of range */
  if (DIO_MAXNOOFPORT <= PortId)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
    LucDetErrFlag = E_OK;
  }
  else
  {
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core for API */
    if((Dio_GaaPortGroup[PortId].ucGroupCoreIndex & LucCoreId) != LucCoreId)                                            /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_PORT_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }

  /* Check if no DET error was reported */
  if (E_NOT_OK == LucDetErrFlag)
  #endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the pointer to the required Port */
    LpPortGroup = &Dio_GaaPortGroup[PortId];

    /* Get the PSRn or JPSR0 address for the required port */
    LpPortAddress = LpPortGroup->pPortAddress;

    /* Check if the required port is Jtag port */
    if (DIO_JTAGPORT == LpPortGroup->ucPortType)
    {
      /*
       * Read the port value from JPPR register by adding offset to
       * PSR register address of Jtag Port
       */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint8, AUTOMATIC, DIO_PRIVATE_DATA))                         /* PRQA S 0751 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_JTAG]));
    }
    else
    {
      /*
       * Read the port value from PPR/APPR register by adding offset to
       * PSR/APSR register address of Numeric/Alphabetic/Analog Port
       */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint16, AUTOMATIC, DIO_PRIVATE_DATA))                        /* PRQA S 0310 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_NONJTAG]));
    }
  } /* else No action required */

  /* Return the Port Level */
  return (LddPortLevel);
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Dio_WritePort
**
** Service ID            : 0x03
**
** Description           : This service writes the specified level to all the
**                         channels in given Port.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : PortId and Level.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaPortGroup
**
**
** Functions Invoked     : Det_ReportError,
**                         SchM_Enter_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL,
**                         SchM_Exit_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL,
**                         Dio_SetPweMode
**
** Registers Used        : PSRn, JPSR0, APSRn.
**
** Reference ID          : DIO_DUD_ACT_002, DIO_DUD_ACT_002_ERR001, DIO_DUD_ACT_002_ERR002
** Reference ID          : DIO_DUD_ACT_002_CRT001, DIO_DUD_ACT_002_REG001,
** Reference ID          : DIO_DUD_ACT_002_CRT002
***********************************************************************************************************************/
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, DIO_PUBLIC_CODE) Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)                                 /* PRQA S 1503 # JV-01 */
{
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  uint32 LulPortGroupNumber;
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;
  
  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  /* Check whether the Port Id is out of range */
  if (DIO_MAXNOOFPORT <= PortId)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
    LucDetErrFlag = E_OK;
  } /* else No action required */
  else
  {
    /* Check invalid core for API */
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    if((Dio_GaaPortGroup[PortId].ucGroupCoreIndex & LucCoreId) != LucCoreId)                                            /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_PORT_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }
  if (E_NOT_OK == LucDetErrFlag)
  #endif
  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the pointer to the required Port */
    LpPortGroup = &Dio_GaaPortGroup[PortId];

    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_ENTER_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
    /* Get the Port Group Number */
    LulPortGroupNumber = LpPortGroup->ulPortGroupNum;

    /* PWE Write Enable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_ENABLE);

    /*
     * Write the Port value using 32-bit PSR register
     * Enable upper 16-bits using mask to effectively write to lower 16-bits
     */
    *(LpPortGroup->pPortAddress) = (((uint32)Level) | (uint32)(~(LpPortGroup->ulModeMask) << 16));

      /* PWE Write Disable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_DISABLE);
   
    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_EXIT_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  } /* else No action required */
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Dio_ReadChannel
**
** Service ID            : 0x00
**
** Description           : This service returns the value of the specified
**                         DIO Channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : ChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Dio_LevelType - STD_HIGH/STD_LOW depending on the
**                         physical level of the Pin
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaPortChannel, Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : PPRn, JPPR0, APPRn
**
** Reference ID          : DIO_DUD_ACT_003, DIO_DUD_ACT_003_ERR001, DIO_DUD_ACT_003_ERR002
***********************************************************************************************************************/
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_ReadChannel(Dio_ChannelType ChannelId)                                         /* PRQA S 1503 # JV-01 */
{
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2CONST(Dio_PortChannelType, DIO_VAR, DIO_PRIVATE_CONST) LpPortChannel;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpPortAddress;                                                            /* PRQA S 3678 # JV-01 */
  Dio_PortLevelType LddPortLevel;
  #endif
  Dio_LevelType LddLevel;
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;

  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  /* Initialize the return value to STD_LOW */
  LddLevel = STD_LOW;

  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;   
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  /* Check whether the Channel Id is out of range */
  if (DIO_MAXNOOFCHANNEL <= ChannelId)
  #endif
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
    LucDetErrFlag = E_OK;
  } /* else No action required */
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  else
  {
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    if((Dio_GaaPortChannel[ChannelId].ucChannelCoreIndex & LucCoreId) != LucCoreId)                                     /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }
  #endif
  if (E_NOT_OK == LucDetErrFlag)
  #endif
  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if at least one Channel is configured */
    #if (DIO_CHANNEL_CONFIGURED == STD_ON)

    /* Get the pointer to the required Channel */
    LpPortChannel = &Dio_GaaPortChannel[ChannelId];

    /* Get the Port Address from Port to which the Channel belongs */
    LpPortGroup = &Dio_GaaPortGroup[LpPortChannel->ucPortIndex];
    LpPortAddress = LpPortGroup->pPortAddress;

    /* Check if the required port is JTAG port */
    if (DIO_JTAGPORT == LpPortGroup->ucPortType)
    {
      /*
       * Read the port value from JPPR register by adding offset to
       * PSR register address of JTAG Port
       */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint8, AUTOMATIC, DIO_PRIVATE_DATA))                         /* PRQA S 0751 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_JTAG]));
    }
    else
    {
      /*
       * Read the port value from PPR/APPR register by adding offset to
       * PSR/APSR register address of Numeric/Alphabetic/Analog Port
       */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint16, AUTOMATIC, DIO_PRIVATE_DATA))                        /* PRQA S 0310 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_NONJTAG]));
    }
    /*
     * Mask the port level value for required Channel bit position and
     * clear other bit positions
     */
    LddPortLevel = LddPortLevel & (LpPortChannel->usMask);

    /* Check whether value is not equal to zero */
    if (DIO_LOW_LEVEL_OUTPUT != LddPortLevel)
    {
      /* Set the return value to STD_HIGH */
      LddLevel = STD_HIGH;
    } /* else No action required */
    #endif
    /* (DIO_CHANNEL_CONFIGURED == STD_ON) */
  } /* else No action required */
  /* Return the Channel Level */
  return LddLevel;
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Dio_WriteChannel
**
** Service ID            : 0x01
**
** Description           : This service writes the given value into the
**                         specified DIO Channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : ChannelId and Level.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaPortChannel, Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError,
**                         SchM_Enter_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL,
**                         SchM_Exit_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL.
**                         Dio_SetPweMode
**
** Registers Used        : PSRn, JPSR0, APSRn
**
** Reference ID          : DIO_DUD_ACT_004, DIO_DUD_ACT_004_ERR001, DIO_DUD_ACT_004_ERR002
** Reference ID          : DIO_DUD_ACT_004_CRT001, DIO_DUD_ACT_004_REG001,
** Reference ID          : DIO_DUD_ACT_004_CRT002
***********************************************************************************************************************/
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, DIO_PUBLIC_CODE) Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)                            /* PRQA S 1503 # JV-01 */
{
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2CONST(Dio_PortChannelType, DIO_VAR, DIO_PRIVATE_CONST) LpPortChannel;
  Dio_PortDataType LunPSRContent;                                                                                       /* PRQA S 0759 # JV-01 */

  uint32 LulPortGroupNumber;
  #endif
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;

  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  /* Check whether the Channel Id is out of range */
  if (DIO_MAXNOOFCHANNEL <= ChannelId)
  #endif
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
    LucDetErrFlag = E_OK;
  }
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  else
  {
    /* Check invalid core for API */
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    if((Dio_GaaPortChannel[ChannelId].ucChannelCoreIndex & LucCoreId) != LucCoreId)                                     /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }
  #endif
  if (E_NOT_OK == LucDetErrFlag)
  #endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if at least one Channel is configured */
    #if (DIO_CHANNEL_CONFIGURED == STD_ON)

    /* Get the pointer to the Port Channel */
    LpPortChannel =&Dio_GaaPortChannel[ChannelId];

    /* Get the pointer to port group to which the channel belongs */
    LpPortGroup = &Dio_GaaPortGroup[LpPortChannel->ucPortIndex];

    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_ENTER_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif

    /*
     * Enable appropriate Channel position by writing
     * upper 16bits of PSR register
     */
    LunPSRContent.Tst_WordValueType.usMSWord = LpPortChannel->usMask;
    /* Check if the input level value is ZERO */
    if (STD_LOW == Level)
    {
      /*
       * Make the Channel value as ZERO by writing
       * lower 16-bits of PSR register
       */
      LunPSRContent.Tst_WordValueType.usLSWord = DIO_LOW_LEVEL_OUTPUT;
    }
    else
    {
      /*
       * Make the Channel value as ONE by writing
       * lower 16-bits of PSR register
       */
      LunPSRContent.Tst_WordValueType.usLSWord = LpPortChannel->usMask;
    }

    /* Get the Port Group Number */
    LulPortGroupNumber = LpPortGroup->ulPortGroupNum;

    /* PWE Write Enable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_ENABLE);

    /* Load 32 bit value to PSR register */
    *(LpPortGroup->pPortAddress) = LunPSRContent.ulLongWord;

    /* PWE Write Disable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_DISABLE);
    
    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_EXIT_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
    #endif
    /* (DIO_CHANNEL_CONFIGURED == STD_ON) */
  } /* else No action required */
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Dio_FlipChannel
**
** Service ID            : 0x11
**
** Description           : This service flip the level of a channel and return
**                         the level of the channel after flip.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : ChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Dio_LevelType - STD_HIGH/STD_LOW depending on the
**                         physical level of the Pin.
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaPortChannel, Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError,
**                         SchM_Enter_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL,
**                         SchM_Exit_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL.
**                         Dio_SetPweMode
**
** Registers Used        : PNOTn, JPNOT0, APNOTn, PPRn, JPPR0, APPR0, PMSRn, JPMSR0, APMSRn.
**
** Reference ID          : DIO_DUD_ACT_005, DIO_DUD_ACT_005_ERR001, DIO_DUD_ACT_005_ERR002
** Reference ID          : DIO_DUD_ACT_005_CRT001, DIO_DUD_ACT_005_REG001,
** Reference ID          : DIO_DUD_ACT_005_CRT002, DIO_DUD_ACT_005_CRT003,
** Reference ID          : DIO_DUD_ACT_005_REG002, DIO_DUD_ACT_005_CRT004
***********************************************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)

#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_FlipChannel(Dio_ChannelType ChannelId)                                         /* PRQA S 1503 # JV-01 */
{
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2CONST(Dio_PortChannelType, DIO_VAR, DIO_PRIVATE_CONST) LpPortChannel;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpPortAddress;
  Dio_PortLevelType LddPortLevel;
  uint32 LulPortModeLevel;
  uint32 LulPortGroupNumber;
  #endif
  Dio_LevelType LddLevel;

  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;

  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  /* Initialize the return value to STD_LOW */
  LddLevel = STD_LOW;

  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  /* Check whether the Channel Id is out of range */
  if (DIO_MAXNOOFCHANNEL <= ChannelId)
  #endif
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_FLIP_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
    LucDetErrFlag = E_OK;
  }
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  else
  {
    /* Check invalid core for API */
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    if((Dio_GaaPortChannel[ChannelId].ucChannelCoreIndex & LucCoreId) != LucCoreId)                                     /* PRQA S 3416, 0404 # JV-01, JV-01 */ 
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_FLIP_CHANNEL_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }
  #endif
  if (E_NOT_OK == LucDetErrFlag)
  #endif
  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if at least one Channel is configured */
    #if (DIO_CHANNEL_CONFIGURED == STD_ON)

    /* Get the pointer to the required Channel */
    LpPortChannel = &Dio_GaaPortChannel[ChannelId];

    /* Get the Port Address in which the Channel is configured */
    LpPortGroup = &Dio_GaaPortGroup[LpPortChannel->ucPortIndex];
    LpPortAddress = LpPortGroup->pPortAddress;
    /* Check if the required port is JTAG port */
    if (DIO_JTAGPORT == LpPortGroup->ucPortType)
    {
      #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
      DIO_ENTER_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      #endif
      LulPortModeLevel = (uint32)(*(&LpPortAddress[(uint32)DIO_PMSR_OFFSET_JTAG])) & LpPortChannel->usMask;
      /* Check if the required port is Output mode */
      if ((uint32)DIO_OUTPUT_MODE_PIN_EXISTENCE_CHECK == LulPortModeLevel)
      {

        /*
         * Write the PNOT register by adding offset to PSR register address
         * for JTAG Port
         */
        *((volatile uint8 *)(&LpPortAddress[(uint32)DIO_PNOT_OFFSET_JTAG])) =  (uint8)(LpPortChannel->usMask);          /* PRQA S 0751 # JV-01 */
      } /* else no operation required */
      /*
       * Read the port value from PPR register by adding offset to
       * PSR register address for JTAG Port
       */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint8, AUTOMATIC, DIO_PRIVATE_DATA))                         /* PRQA S 0751 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_JTAG]));
      #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
      DIO_EXIT_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      #endif
    }
    /* (DIO_NORMALPORT == LpPortGroup->ucPortType) */
    else
    {
      #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
      DIO_ENTER_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      #endif

      LulPortModeLevel = (uint32)(*(&LpPortAddress[(uint32)DIO_PMSR_OFFSET_NONJTAG])) & LpPortChannel->usMask;
      if ((uint32)DIO_OUTPUT_MODE_PIN_EXISTENCE_CHECK == LulPortModeLevel)
      {
        /* Get the Port Group Number */
        LulPortGroupNumber = LpPortGroup->ulPortGroupNum;

        /* PWE Write Enable for each Port Group */
        Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_ENABLE);

        /*
         * Write the PNOT/APNOT register by adding offset to PSR register address
         * for for Numeric/Alphabetic Port
         */
        *((volatile uint16 *)(&LpPortAddress[(uint32)DIO_PNOT_OFFSET_NONJTAG]))                                         /* PRQA S 0310 # JV-01 */
            = LpPortChannel->usMask;

        /* PWE Write Disable for each Port Group */
        Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_DISABLE);
      } /* else no operation required */
      /*
       * Read the port value from PPR/APPR register by adding offset to
       * PSR/APSR register address for Numeric/Alphabetic Port
       */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint16, AUTOMATIC, DIO_PRIVATE_DATA))                        /* PRQA S 0310 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_NONJTAG]));

      #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
      DIO_EXIT_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      #endif
    }
    /*
     * Mask the port value for required Channel bit position and
     * clear other bit positions
     */
    LddPortLevel = LddPortLevel & (LpPortChannel->usMask);

    /* Check whether value is not equal to zero */
    if (DIO_LOW_LEVEL_OUTPUT != LddPortLevel)
    {
      /* Set the return value to STD_HIGH */
      LddLevel = STD_HIGH;
    } /* else No action required */
    #endif
   /* (DIO_CHANNEL_CONFIGURED == STD_ON) */
  } /* else No action required */
  /* Return the Channel Level */
  return (LddLevel);
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif
/* #if (DIO_FLIP_CHANNEL_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Dio_ReadChannelGroup
**
** Service ID            : 0x04
**
** Description           : This service returns the value of the ChannelGroup
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : ChannelGroupIdPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Dio_PortLevelType
**
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaChannelGroupData, Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : PPRn, JPPR0, APPRn.
**
** Reference ID          : DIO_DUD_ACT_006, DIO_DUD_ACT_006_ERR001,
** Reference ID          : DIO_DUD_ACT_006_ERR002, DIO_DUD_ACT_006_ERR003
***********************************************************************************************************************/
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE)
Dio_ReadChannelGroup(P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_CONST) ChannelGroupIdPtr)                               /* PRQA S 1503, 3206 # JV-01, JV-01 */
{
  #if (DIO_CHANNELGROUP_CONFIGURED == STD_ON)
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpChannelGroupPtr;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpPortAddress;                                                            /* PRQA S 3678 # JV-01 */                       
  #endif

  Dio_PortLevelType LddPortLevel;

  #if (DIO_CHANNELGROUP_CONFIGURED == STD_ON)
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;
  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif
  #endif

  /* Set the return value to 0 */
  LddPortLevel = DIO_LOW_LEVEL_OUTPUT;                                                                                  /* PRQA S 2982 # JV-01 */

  /* Check if at least one ChannelGroup is configured */
  #if (DIO_CHANNELGROUP_CONFIGURED == STD_ON)
  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  /* Check whether LpChannelGroupPtr is NULL_PTR */
  if (NULL_PTR == ChannelGroupIdPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
    LucDetErrFlag = E_OK;
  }
  else
  {
    LpChannelGroupPtr = ChannelGroupIdPtr;
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core for API */
    if((LpChannelGroupPtr->ucChannelGroupCoreIndex & LucCoreId) != LucCoreId)                                           /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif
  }

  if (E_NOT_OK == LucDetErrFlag)
  #else
  LpChannelGroupPtr = ChannelGroupIdPtr;
  #endif
  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the Port Address in which the Channel is configured */
    LpPortGroup = &Dio_GaaPortGroup[LpChannelGroupPtr->ucPortIndex];
    LpPortAddress = LpPortGroup->pPortAddress;

    /* Check if the required port is JTAG port */
    if (DIO_JTAGPORT == LpPortGroup->ucPortType)
    {
      /* Read the port value from JPPR register by adding offset to */
      /* JPSR register address for JTAG Port                        */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint8, AUTOMATIC, DIO_PRIVATE_DATA))                         /* PRQA S 0751 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_JTAG]));
    }
    else
    {
      /* Read the port value from PPR/APPR register by adding offset to */
      /* PSR/APSR register address for Numeric/Alphabetic Port          */
      LddPortLevel = (Dio_PortLevelType)(*((P2VAR(volatile uint16, AUTOMATIC, DIO_PRIVATE_DATA))                        /* PRQA S 0310 # JV-01 */
                                           & LpPortAddress[(uint32)DIO_PPR_OFFSET_NONJTAG]));
    }
    /*
     * Mask the port value for required ChannelGroup related bit positions
     * and clear other bit positions
     */
    LddPortLevel = LddPortLevel & (LpChannelGroupPtr->usMask);

    /* Rotate right to get the corresponding ChannelGroup value */
    LddPortLevel = LddPortLevel >> (LpChannelGroupPtr->ucOffset);
  } /* else No action required */
  #else
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Report Error to DET */
  (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
  #endif
  /* (DIO_CHANNELGROUP_CONFIGURED == STD_ON) */
  #endif
  /* Return the ChannelGroup Level */
  return (LddPortLevel);
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Dio_WriteChannelGroup
**
** Service ID            : 0x05
**
** Description           : This service writes specified level to the
**                         ChannelGroup
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : ChannelGroupIdPtr and Level.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaChannelGroupData, Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError,
**                         SchM_Enter_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL,
**                         SchM_Exit_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL.
**                         Dio_SetPweMode
**
** Registers Used        : PSRn, JPSR0, APSRn.
**
** Reference ID          : DIO_DUD_ACT_007, DIO_DUD_ACT_007_ERR001, DIO_DUD_ACT_007_ERR003
** Reference ID          : DIO_DUD_ACT_007_ERR002, DIO_DUD_ACT_007_CRT001,
** Reference ID          : DIO_DUD_ACT_007_REG001, DIO_DUD_ACT_007_CRT002
** Reference ID          : DIO_DUD_ACT_007_REG002
***********************************************************************************************************************/
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, DIO_PUBLIC_CODE)
Dio_WriteChannelGroup(P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_CONST) ChannelGroupIdPtr, Dio_PortLevelType Level)     /* PRQA S 1503, 3206 # JV-01, JV-01 */
{
  #if (DIO_CHANNELGROUP_CONFIGURED == STD_ON)
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpChannelGroupPtr;
  Dio_PortDataType LunPSRContent;                                                                                       /* PRQA S 0759 # JV-01 */
  uint32 LulPortGroupNumber;
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucDetErrFlag;
  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  LucDetErrFlag = E_NOT_OK;
  /* Check whether ChannelGroupIdPtr is NULL_PTR */
  if (NULL_PTR == ChannelGroupIdPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
    LucDetErrFlag = E_OK;
  }
  else
  {
    /* Get the pointer to corresponding index in the
    array Dio_GaaChannelGroupData */
    LpChannelGroupPtr = ChannelGroupIdPtr;
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core for API */
    if((LpChannelGroupPtr->ucChannelGroupCoreIndex & LucCoreId) != LucCoreId)                                           /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif
  }

  if (E_NOT_OK == LucDetErrFlag)
  #else /* (DIO_DEV_ERROR_DETECT == STD_OFF) */
  /* Get the pointer to corresponding index in the
  array Dio_GaaChannelGroupData */
  LpChannelGroupPtr = ChannelGroupIdPtr;
  #endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the pointer to port group to which the channel belongs */
    LpPortGroup = &Dio_GaaPortGroup[LpChannelGroupPtr->ucPortIndex];

    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_ENTER_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif

    /* Rotate left the input level to get the value to be written to port */
    Level = (Dio_PortLevelType)(Level << (LpChannelGroupPtr->ucOffset));                                                /* PRQA S 1338 # JV-01 */
    /*
     * Enable appropriate ChannelGroup related positions
     * by writing upper 16-bits of PSR register
     */
    LunPSRContent.Tst_WordValueType.usMSWord = LpChannelGroupPtr->usMask;
    /* Write the Level value to lower 16-bits of PSR register*/
    LunPSRContent.Tst_WordValueType.usLSWord = Level & ~(LpPortGroup->ulModeMask);                                      /* PRQA S 4461 # JV-01 */

    /* Get the Port Group Number */
    LulPortGroupNumber = LpPortGroup->ulPortGroupNum;

    /* PWE Write Enable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_ENABLE);

    /*Load 32 bit value to PSR register*/
    *(LpPortGroup->pPortAddress) = LunPSRContent.ulLongWord;

    /* PWE Write Disable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_DISABLE);

    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_EXIT_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  } /* else No action required */
  #else
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Report Error to DET */
  (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
  #endif
  /* (DIO_CHANNELGROUP_CONFIGURED == STD_ON) */
  #endif
}
#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Dio_GetVersionInfo
**
** Service ID            : 0x12
**
** Description           : This API returns the version information of DIO
**                         driver component.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : versioninfo
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : None
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : DIO_DUD_ACT_012, DIO_DUD_ACT_012_ERR001
***********************************************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, DIO_PUBLIC_CODE) Dio_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
  }
  else
  #endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
    versioninfo->moduleID = (uint16)DIO_MODULE_ID;
    versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
  }
}
#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (DIO_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Dio_MaskedWritePort
**
** Service ID            : 0x13
**
** Description           : This service writes the specified level to all the
**                         channels that are Masked in given Port.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : PortId, Mask and Level.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError,
**                         SchM_Enter_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL,
**                         SchM_Exit_Dio_DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL.
**                         Dio_SetPweMode
**
** Registers Used        : PSRn, JPSR0, APSRn.
**
** Reference ID          : DIO_DUD_ACT_008, DIO_DUD_ACT_008_ERR001, DIO_DUD_ACT_008_ERR002
** Reference ID          : DIO_DUD_ACT_008_CRT001, DIO_DUD_ACT_008_REG001,
** Reference ID          : DIO_DUD_ACT_008_CRT002, DIO_DUD_ACT_008_REG002
***********************************************************************************************************************/

#if (DIO_MASKED_WRITE_PORT_API == STD_ON)

#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, DIO_PUBLIC_CODE)
Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask)                               /* PRQA S 1503 # JV-01 */
{
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  Dio_PortDataType LunPSRContent;                                                                                       /* PRQA S 0759 # JV-01 */
  uint32 LulPortGroupNumber;
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;
  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  /* Check whether the Port Id is out of range */
  if (DIO_MAXNOOFPORT <= PortId)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_MASKED_WRITE_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
    LucDetErrFlag = E_OK;
  }
  else
  {
    /* Check invalid core for API */
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core for API */
    if((Dio_GaaPortGroup[PortId].ucGroupCoreIndex & LucCoreId) != LucCoreId)                                         /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_MASKED_WRITE_PORT_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }

  if (E_NOT_OK == LucDetErrFlag)
  #endif
  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the pointer to the required Port */
    LpPortGroup = &Dio_GaaPortGroup[PortId];

    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_ENTER_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif

    /*
      * Enable appropriate ChannelGroup related positions
      * by writing upper 16-bits of PSR register
      */
    LunPSRContent.Tst_WordValueType.usMSWord = Mask & ~(LpPortGroup->ulModeMask);                                    /* PRQA S 4461 # JV-01 */

    /* Write the Level value to lower 16-bits of PSR register*/
    LunPSRContent.Tst_WordValueType.usLSWord = Level & ~(LpPortGroup->ulModeMask);                                   /* PRQA S 4461 # JV-01 */

    /* Get the Port Group Number */
    LulPortGroupNumber = LpPortGroup->ulPortGroupNum;

    /* PWE Write Enable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_ENABLE);

    /*Load 32 bit value to PSR register*/
    *(LpPortGroup->pPortAddress) = LunPSRContent.ulLongWord;

    /* PWE Write Disable for each Port Group */
    Dio_SetPweMode(LulPortGroupNumber, DIO_PWE_EACH_WRITE_DISABLE);
    
    #if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
    DIO_EXIT_CRITICAL_SECTION(DIO_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  } /* else No action required */
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif
/* STD_ON == DIO_MASKED_WRITE_PORT_API */

/***********************************************************************************************************************
** Function Name         : Dio_ReadChannelOutputValue
**
** Service ID            : 0x14
**
** Description           : This service returns the output value of the
**                         specified DIO Channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Dio_LevelType - STD_HIGH/STD_LOW depending on the
**                         output data of the Pin
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaPortChannel, Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : PSRn, JPSR0, APSRn.
**
** Reference ID          : DIO_DUD_ACT_009, DIO_DUD_ACT_009_ERR001, DIO_DUD_ACT_009_ERR002
***********************************************************************************************************************/
#if (DIO_READ_CHANNEL_OUTPUT_VALUE_API == STD_ON)

#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_ReadChannelOutputValue(const Dio_ChannelType LddChannelId)                     /* PRQA S 1503 # JV-01 */
{
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2CONST(Dio_PortChannelType, DIO_VAR, DIO_PRIVATE_CONST) LpPortChannel;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpPortAddress;                                                            /* PRQA S 3678 # JV-01 */
  uint32 LulPortRegValueTmp;
  uint16 LusPortRegValue;
  /*  LusPortRegValue = DIO_PORT_REGISTER_DEFAULT_VALUE; */
  #endif
  Dio_LevelType LddLevel;

  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;
  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif

  /* Initialize the return value to STD_LOW */
  LddLevel = STD_LOW;

  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  /* Check whether the Channel Id is out of range */
  if (DIO_MAXNOOFCHANNEL <= LddChannelId)
  #endif
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_OUTPUT_VALUE_SID,
                          DIO_E_PARAM_INVALID_CHANNEL_ID);
    LucDetErrFlag = E_OK;
  }
  #if (DIO_CHANNEL_CONFIGURED == STD_ON)
  else
  {
    /* Check invalid core for API */
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core for API */
    if((Dio_GaaPortChannel[LddChannelId].ucChannelCoreIndex & LucCoreId) != LucCoreId)                                  /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_OUTPUT_VALUE_SID, DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }
  #endif
  if (E_NOT_OK == LucDetErrFlag)
  #endif
  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if at least one Channel is configured */
    #if (DIO_CHANNEL_CONFIGURED == STD_ON)

    /* Get the pointer to the required Channel */
    LpPortChannel = &Dio_GaaPortChannel[LddChannelId];

    /* Get the Port Address from Port to which the Channel belongs */
    LpPortGroup = &Dio_GaaPortGroup[LpPortChannel->ucPortIndex];
    LpPortAddress = LpPortGroup->pPortAddress;

    /* Read the port value from PSR(JPSR) register */
    /* PSRn_[31:16] Read value is always returned 0000H. */
    /* PSRn_[15:0] Read value is returned Pn register value. */
    LulPortRegValueTmp = *(LpPortAddress);
    LusPortRegValue = (uint16)LulPortRegValueTmp;

    /*
     * Mask the port level value for required Channel bit position and
     * clear other bit positions
     */
    LusPortRegValue = LusPortRegValue & (LpPortChannel->usMask);

    /* Check whether value is not equal to zero */
    if (DIO_LOW_LEVEL_OUTPUT != LusPortRegValue)
    {
      /* Set the return value to STD_HIGH */
      LddLevel = STD_HIGH;
    } /* else No action required */
    #endif
    /* (DIO_CHANNEL_CONFIGURED == STD_ON) */
  } /* else No action required */
  /* Return the Channel Level */
  return LddLevel;
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif
/* STD_ON == DIO_READ_CHANNEL_OUTPUT_VALUE_API */

/***********************************************************************************************************************
** Function Name         : Dio_ReadChannelGroupOutputValue
**
** Service ID            : 0x15
**
** Description           : This service returns the output value of the
**                         specified DIO Channel Group.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : ChannelGroupIdPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Dio_PortLevelType
**
**
** Preconditions         : None
**
** Global Variables Used : Dio_GaaChannelGroupData, Dio_GaaPortGroup
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : PSRn, JPSR0, APSRn.
**
** Reference ID          : DIO_DUD_ACT_010, DIO_DUD_ACT_010_ERR001,
** Reference ID          : DIO_DUD_ACT_010_ERR002, DIO_DUD_ACT_010_ERR003
***********************************************************************************************************************/
#if (DIO_READ_CHANNELGROUP_OUTPUT_VALUE_API == STD_ON)

#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE)
Dio_ReadChannelGroupOutputValue(P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_CONST) ChannelGroupIdPtr)                    /* PRQA S 1503, 3206 # JV-01, JV-01 */
{
  #if (DIO_CHANNELGROUP_CONFIGURED == STD_ON)
  P2CONST(Dio_PortGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpPortGroup;
  P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_PRIVATE_CONST) LpChannelGroupPtr;
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpPortAddress;                                                            /* PRQA S 3678 # JV-01 */
  uint32 LulPortRegValueTmp;
  #endif

  Dio_PortLevelType LddPortLevel;

  #if (DIO_CHANNELGROUP_CONFIGURED == STD_ON)
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucDetErrFlag;
  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for curent core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreId;
  /* Get the current core ID by OS service */
  LucCoreId = DIO_ONE << (uint8)GetCoreID();
  #endif /* (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  #endif
  #endif

  /* Set the return value to 0 */
  LddPortLevel = DIO_LOW_LEVEL_OUTPUT;                                                                                  /* PRQA S 2982 # JV-01 */

  /* Check if at least one ChannelGroup is configured */
  #if (DIO_CHANNELGROUP_CONFIGURED == STD_ON)
  /* Check whether DIO_DEV_ERROR_DETECT is enabled */
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_NOT_OK;
  /* Check whether LpChannelGroupPtr is NULL_PTR */
  if (NULL_PTR == ChannelGroupIdPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_OUTPUT_VALUE_SID, DIO_E_PARAM_POINTER);
    LucDetErrFlag = E_OK;
  }
  else
  {
    LpChannelGroupPtr = ChannelGroupIdPtr;
    /* Check invalid core for API */
    #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core for API */
    if((LpChannelGroupPtr->ucChannelGroupCoreIndex & LucCoreId) != LucCoreId)                                           /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_OUTPUT_VALUE_SID, 
                                                                                                  DIO_E_INVALID_CORE);
      /* Set the error status flag to E_OK */
      LucDetErrFlag = E_OK;
    } /* else No action required */
    #endif /* #if (DIO_MULTI_CORE_SUPPORT == STD_ON) */
  }

  if (E_NOT_OK == LucDetErrFlag)
  #else
  LpChannelGroupPtr = ChannelGroupIdPtr;
  #endif
  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the Port Address in which the Channel is configured */
    LpPortGroup = &Dio_GaaPortGroup[LpChannelGroupPtr->ucPortIndex];
    LpPortAddress = LpPortGroup->pPortAddress;

    /* Read the port value from PSR(JPSR) register */
    /* PSRn_[31:16] Read value is always returned 0000H. */
    /* PSRn_[15:0] Read value is returned Pn register value. */
    LulPortRegValueTmp = *(LpPortAddress);
    LddPortLevel = (uint16)LulPortRegValueTmp;

    /*
     * Mask the port value for required ChannelGroup related bit positions
     * and clear other bit positions
     */
    LddPortLevel = LddPortLevel & (LpChannelGroupPtr->usMask);

    /* Rotate right to get the corresponding ChannelGroup value */
    LddPortLevel = LddPortLevel >> (LpChannelGroupPtr->ucOffset);
  } /* else No action required */
  #else
    #if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Report Error to DET */
    (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_OUTPUT_VALUE_SID,
                        DIO_E_PARAM_INVALID_GROUP);
    #endif
  #endif
  /* (DIO_CHANNELGROUP_CONFIGURED == STD_ON) */
  /* Return the ChannelGroup Level */
  return (LddPortLevel);
}

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/* STD_ON == DIO_READ_CHANNELGROUP_OUTPUT_VALUE_API */

/***********************************************************************************************************************
** Function Name         : Dio_SetPweMode
**
** Service ID            : NA
**
** Description           : This function used to set the PWE mode of Port Group
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : uint32 - LulGroup :Port Group Number,
**                       : uint8 - LucMode :Protection Mode
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : DIO_GaaPweData
**
** Functions Invoked     : None
**
** Registers Used        : PKCPROT, PWE
**
** Reference ID          : DIO_DUD_ACT_011, DIO_DUD_ACT_011_REG001,
** Reference ID          : DIO_DUD_ACT_011_REG002, DIO_DUD_ACT_011_REG003
***********************************************************************************************************************/
/***********************************************************************************************************************
** Input Parameters Conditions
** Mode                       Group
** DIO_PWE_EACH_WRITE_DISABLE 0..
** DIO_PWE_EACH_WRITE_ENABLE  0..
**
***********************************************************************************************************************/
#define DIO_START_SEC_PRIVATE_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, DIO_PRIVATE_CODE) Dio_SetPweMode(const uint32 LulGroup, const uint8 LucMode)
{
  uint32 LulPweEnableValue;

  /* Load PWE Enable Value for requested Dio Group */
  LulPweEnableValue = DIO_GaaPweData[LulGroup];
  /* Check Invalid Dio Group request */
  if (DIO_PWE_INVALID_VALUE != LulPweEnableValue)
  {
    if (DIO_PWE_EACH_WRITE_DISABLE == LucMode)
    {
      /* Set Write Disable value */
      LulPweEnableValue = DIO_PWE_REG & ~LulPweEnableValue;                                                             /* PRQA S 0303 # JV-01 */
    }
    else if (DIO_PWE_EACH_WRITE_ENABLE == LucMode)
    {
      /* Set Write Enable value */
      LulPweEnableValue = DIO_PWE_REG | LulPweEnableValue;                                                              /* PRQA S 0303 # JV-01 */
    }
    else
    {
      /* No action required */
      LulPweEnableValue = DIO_PWE_INVALID_VALUE;
    }
  } /* else No action required */

  /* Check if PWE control valid */
  if (DIO_PWE_INVALID_VALUE != LulPweEnableValue)
  {
    /* Enable PWE writing */
    DIO_PKCPROT_REG = DIO_WRITE_PWE_ENABLE_VAL;                                                                         /* PRQA S 0303 # JV-01 */

    /* Write PWE value */
    DIO_PWE_REG = LulPweEnableValue;                                                                                    /* PRQA S 0303 # JV-01 */

    /* Disable PWE writing */
    DIO_PKCPROT_REG = DIO_WRITE_PWE_DISABLE_VAL;                                                                        /* PRQA S 0303 # JV-01 */
  } /* else No action required */

} /* End of Dio_SetPweMode */
#define DIO_STOP_SEC_PRIVATE_CODE
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
