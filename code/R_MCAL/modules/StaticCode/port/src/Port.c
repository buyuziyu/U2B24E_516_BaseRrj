/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port.c                                                                                              */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of PORT Driver                                                                        */
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
 *                   : In Port_Init, Port_RefreshPortDirection, Port_EcmMaskERRORIN, Port_EcmClearERRORIN:
 *                     Update to use ucPortKernelCoreId for condition check core ID 
 *                     Add msg 3416 for Port_GpConfigPtr->ucPortKernelCoreId
 * 2.0.1: 07/11/2023 : In Port_RefreshPortDirection, Port_SetPinMode, Port_EcmMaskERRORIN, Port_EcmClearERRORIN: 
 *                     Add SchM_Enter_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL() 
 *                     and SchM_Exit_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL() to Functions invoked
 *                     In Port_SetPinDirection remove one duplicate Det_ReportError in Functions invoked 
 *                     In Port_EcmMaskERRORIN, Port_EcmClearERRORIN remove register used 
 *                     in function info (Register Used field) 
 *        19/10/2023 : Add the information for Msg 3415, Msg 2995
 *                     Add "PRQA S 2995 # JV-01", "PRQA S 3416 # JV-01", "PRQA S 3415 # JV-01"
 *                     Remove Msg 0857, 2814, 2824, 2844
 *        12/10/2023 : In APIs Port_SetPinDirection, Port_RefreshPortDirection, Port_SetPinMode, 
 *                     Port_SetPinDefaultDirection : Move checking of PORT_E_UNINIT to be performed first
 * 2.0.0: 26/08/2023 : Update coding rule for correct 120character/line 
 *        18/08/2023 : Update description for functions not use Port_GusLockPWE
 *        08/08/2023 : In function Port_SetPinMode: Remove condition to check register PWE enable or disable
 *        07/08/2023 : Update description for Port_Init, Port_SetPinDirection, Port_SetPinMode
 *        06/08/2023 : Update CWE Rule for message 0316, 1503, 2004, 2814, 2824, 2844, 2905, 3416, 3432
 *        01/08/2023 : Update to support for Multicore type III in Port:
 *                     Add new include header "Os.h".
 *                     Update APIs to check core running: Port_Init, Port_SetPinDirection, Port_RefreshPortDirection, 
 *                     Port_SetPinMode, Port_SetPinDefaultDirection, Port_EcmMaskERRORIN, Port_EcmClearERRORIN
 *                     Change critical section in APIs Port_SetPinDirection to internal function Port_SwitchSetting 
 *                     in APIs: Port_SetPinDefaultDirection, Port_SetPinDirection
 *                     Update critical section call from PORT_INTERRUPT_CONTROL_PROTECTION to 
 *                     PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL in APIs: Port_RefreshPortDirection, Port_SetPinMode
 *        27/06/2023 : Remove redundant QAC message
 *        26/06/2023 : Update description for functions
 *        22/05/2023 : Remove redundant QAC message
 * 1.5.0: 26/04/2023 : Update SW-VERSION to 2.0.0
 * 1.4.5: 08/13/2022 : Update condition for calling Port_InitConfig(PORT_RESET) function in Port_Init API
 * 1.4.4: 12/07/2022 : Update condition for Det_ReportError in cases unavailable mode in Port_SetPinMode API
 *        07/07/2022 : Fix QAC message "PRQA S 0857 # JV-01"
 *        22/06/2022 : Add QAC header
 *                     Add QAC message "PRQA S 0857 # JV-01", "PRQA S 2004 # JV-01"
 *        18/06/2022 : Add Det_ReportError for cases unavailable mode in Port_SetPinMode API.
 * 1.4.3: 23/05/2022 : Fix QAC header and message.
 *        14/05/2022 : Add Pre-Condition for Port_EcmMaskERRORIN and Port_EcmClearERRORIN API.
 *        09/05/2022 : Remove conditions: if(LusPortLoc >= Port_TypeInformation[LusPortType].usPortNum),
 *                     if(LusBitLoc != (LpPortInfo->stRegInfo[PORT_REG_PM].usValid & LusBitLoc)) and all commands in 
 *                     that conditions from Port_SetPinDirection function.
 *                     Remove condition: if(LusPortLoc >= Port_TypeInformation[LusPortType].usPortNum) and all commands
 *                     in this condition from Port_RefreshPortDirection function.
 *                     Remove conditions: if(LusPortLoc >= Port_TypeInformation[LusPortType].usPortNum), 
 *                     if((LusBitLoc != (LpPortInfo->stRegInfo[PORT_REG_PMC].usValid & LusBitLoc)) &&
 *                     (LusBitLoc != (LpPortInfo->stRegInfo[PORT_REG_PM].usValid & LusBitLoc))) and all commands in
 *                     that conditions from Port_SetPinMode function.
 *                     Remove conditions: if(LusPortLoc >= Port_TypeInformation[LusPortType].usPortNum),  
 *                     if (LusBitLoc != (LpPortInfo->stRegInfo[PORT_REG_PM].usValid & LusBitLoc)) and all commands in
 *                     that conditions from Port_SetPinDefaultDirection function.
 *                     Remove LpPortInfo variable in Port_SetPinMode function
 *                     Remove "else" statement when no action required
 *                     Add condition #if (PORT_E_WRITE_TIMEOUT_FAILURE_CONFIGURED == STD_ON) for 
 *                     PORT_DEM_REPORT_ERROR in Port_Init.
 *        14/04/2022 : Remove condition #if (PORT_DEM_ERROR_DETECT == STD_ON) for PORT_DEM_REPORT_ERROR in Port_Init.
 *        12/04/2022 : Update SW-VERSION to 1.4.3
 * 1.4.1: 07/10/2021 : Update SW-VERSION to 1.4.1
 * 1.3.2: 25/08/2021 : As per ticket #ARDAACL-2156, correct condition from APORT to PMC register in API:
 *                     Port_SetPinDirection and Port_SetPinDefaultDirection.
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0
 *                     Format source code to 120 characters
 *                     Improve Violation tag (remove START/END)
 * 1.3.1: 06/05/2021 : Fixed coding rule violation as per ticket #ARDAACL-224
 *                     - Style_Format_008: Remove space before '++'.
 * 1.3.0: 20/01/2021 : Correct prototype of Port_SetPinDirection, Port_SetPinMode
 *                     in order to comply AUTOSAR specification.
 *        09/11/2020 : Update Port_RefreshPortDirection to support PIBC setting
 * 1.2.0: 28/07/2020 : Release.
 * 1.1.0: 19/06/2020 : Release.
 * 1.0.1: 21/04/2020 : Re-design Port_RefreshPortDirection due to
 *                     performance issue.
 * 1.0.0: 09/01/2020 : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Port APIs header file */
#include "Port.h"
#if (PORT_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif
/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"
/* Included for RAM variable declarations */
#include "Port_Ram.h"
/* Included for Header file inclusion */
#include "Port_LLDriver.h"

#if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Port.h"
#endif

#if (PORT_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PORT_C_AR_RELEASE_MAJOR_VERSION    PORT_AR_RELEASE_MAJOR_VERSION_VALUE
#define PORT_C_AR_RELEASE_MINOR_VERSION    PORT_AR_RELEASE_MINOR_VERSION_VALUE
#define PORT_C_AR_RELEASE_REVISION_VERSION PORT_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define PORT_C_SW_MAJOR_VERSION            PORT_SW_MAJOR_VERSION_VALUE
#define PORT_C_SW_MINOR_VERSION            PORT_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (PORT_AR_RELEASE_MAJOR_VERSION != PORT_C_AR_RELEASE_MAJOR_VERSION)
  #error "Port.c : Mismatch in Release Major Version"
#endif
#if (PORT_AR_RELEASE_MINOR_VERSION != PORT_C_AR_RELEASE_MINOR_VERSION)
  #error "Port.c : Mismatch in Release Minor Version"
#endif
#if (PORT_AR_RELEASE_REVISION_VERSION != PORT_C_AR_RELEASE_REVISION_VERSION)
  #error "Port.c : Mismatch in Release Revision Version"
#endif

#if (PORT_SW_MAJOR_VERSION != PORT_C_SW_MAJOR_VERSION)
  #error "Port.c : Mismatch in Software Major Version"
#endif
#if (PORT_SW_MINOR_VERSION != PORT_C_SW_MINOR_VERSION)
  #error "Port.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM MSC01, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2905)    : Constant: Positive integer value truncated by cast to a smaller unsigned type.               */
/* Rule                : CERTCCM INT31, CWE Rule CWE-197, CWE-681, CWE-704, CWE-192, CWE-738                          */
/* JV-01 Justification : To perform 8bit operations on a 16bit register, a cast to uint8 is required.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define PORT_START_SEC_PRIVATE_CODE
#include "Port_MemMap.h"

STATIC FUNC(void, PORT_PRIVATE_CODE) Port_SetStatus(const boolean LblStatus);

#define PORT_STOP_SEC_PRIVATE_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Port_Init
**
** Service ID            : 0x00
**
** Description           : This service performs initialization of the PORT
**                         Driver components.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : ConfigPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Port_GpConfigPtr, Port_GpPortPinConfig, Port_GpPortConfig, Port_GpPortDNFConfig, 
**                         Port_GusLockPWE
**
** Functions Invoked     : Det_ReportError, Port_SetPweMode, Port_InitConfig, Port_InitDNF,
**                         Port_SetStatus, Port_MaskECM, Port_ClearECM, PORT_DEM_REPORT_ERROR
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_001, PORT_DUD_ACT_001_ERR001,
** Reference ID          : PORT_DUD_ACT_001_ERR002, PORT_DUD_ACT_001_ERR003
** Reference ID          : PORT_DUD_ACT_001_ERR004, PORT_DUD_ACT_001_ERR005
** Reference ID          : PORT_DUD_ACT_001_GBL001, PORT_DUD_ACT_001_GBL002
** Reference ID          : PORT_DUD_ACT_001_GBL003, PORT_DUD_ACT_001_GBL004, PORT_DUD_ACT_001_GBL005
***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_Init(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr)                  /* PRQA S 1503 # JV-01 */
{
  /* Variable to get result of Port_InitConfig */
  Std_ReturnType LucResult;
  boolean LblERRORIN;
  uint16 LusCnt;

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint16 LusPortLoc;
  uint16 LusPortType;
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

  LucResult = E_OK;

  /* Report to DET, if the configuration pointer value is NULL */
  if (NULL_PTR == ConfigPtr)
  {
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_INIT_FAILED);
    #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
    LucResult = E_NOT_OK; 
  } /* End of ConfigPtr == NULL_PTR */
  else
  {
    #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
    if ((ConfigPtr->ucPortKernelCoreId) != LucCoreId)
    {
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_INVALID_CORE);
      #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
      /* Set Result value as E_NOT_OK */
      LucResult = E_NOT_OK;
    }
    else
    #endif /* #if (PORT_MUTLI_CORE_SUPPORT == STD_ON) */
    {
      if (PORT_DBTOC_VALUE != (ConfigPtr->ulStartOfDbToc))
      {
        #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_INVALID_DATABASE);
        #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
        LucResult = E_NOT_OK;
      } /* Else no action required */
    }
  }

  if (E_OK == LucResult)
  {
    /* Assign the configuration pointer value to global pointer */
    Port_GpConfigPtr = ConfigPtr;

    Port_GpPortPinConfig = (P2CONST(Port_Pin_Config, PORT_VAR, PORT_CONFIG_DATA))Port_GpConfigPtr->pPortPinConfig;      /* PRQA S 0316 # JV-01 */
    Port_GpPortDNFConfig = (P2CONST(Port_DNF_Init, PORT_VAR, PORT_CONFIG_DATA))Port_GpConfigPtr->pPortDNFConfig;        /* PRQA S 0316 # JV-01 */
    for (LusCnt = (uint16)PORT_ZERO; LusCnt < PORT_TYPE_NUM; LusCnt++)
    {
      Port_GpPortConfig[LusCnt] =
                            (P2CONST(Port_Reg_Init, PORT_VAR, PORT_CONFIG_DATA))Port_GpConfigPtr->pPortConfig[LusCnt];  /* PRQA S 0316 # JV-01 */
    }

    /* Save the current mask value of ERRORIN,
       Mask the ECM error output signal of ERRORIN */
    LblERRORIN = Port_MaskECM(PORT_MASK);
    /* Set Enable to all bit of PWE */
    Port_SetPweMode((uint16)PORT_DEFAULT, (uint16)PORT_DEFAULT, PORT_ENABLE);                                           /* PRQA S 2905 # JV-01 */
    /* Set each value after reset */
    LucResult = Port_InitConfig(PORT_RESET);

    if (E_OK == LucResult)
    {
      /* Invoking Port_InitDNF() for configuration of filter registers */
      LucResult = Port_InitDNF();
    } /* Else No action required */

    if (E_OK == LucResult)
    {
      /* Initialize port registers with the configuration set */
      LucResult = Port_InitConfig(PORT_INIT);
    } /* Else No action required */

    /* Set Disable to all bit of PWE */
    Port_SetPweMode((uint16)PORT_DEFAULT, (uint16)PORT_DEFAULT, PORT_DISABLE);                                          /* PRQA S 2905 # JV-01 */

    /* Clear the ECM error status of ERRORIN */
    Port_ClearECM();
    /* Set Unmask/Mask the ECM error output signal of ERRORIN */
    if (PORT_UNMASK == LblERRORIN)
    {
      (void)Port_MaskECM(PORT_UNMASK);
    } /* Else No action required */

    /* Check for complete the Port Group initialize */
    if (E_OK == LucResult)
    {
      /* Set the Port status to Initialized */
      Port_SetStatus(PORT_INITIALIZED);

      #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
      for (LusPortType = (uint16)PORT_ZERO; LusPortType < PORT_TYPE_NUM; LusPortType++)
      {
        /* Set the Port Port Write Enable (PWE) register to PORT ZERO for each port group */
        for (LusPortLoc = (uint16)PORT_ZERO; LusPortLoc < (uint16)Port_TypeInformation[LusPortType].usPortNum; 
                                                                                                          LusPortLoc++)
        {
          Port_GusLockPWE[LusPortType][LusPortLoc] = (uint16)PORT_ZERO;
        } /* Else no action required */
      }
      #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */
    }
    else /* Initialize failed */
    {
      #if (PORT_E_WRITE_TIMEOUT_FAILURE_CONFIGURED == STD_ON)
      /* Report write failure production error */
      PORT_DEM_REPORT_ERROR(PORT_E_WRITE_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
      #endif
    }
  } /* Else No action required */
} /* End of API Port_Init */

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_SetPinDirection
**
** Service ID            : 0x01
**
** Description           : This service sets the port pin direction during
**                         runtime.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Pin - Port Pin ID number
**                         Direction - Port Pin Direction
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Ports should be initialized by calling Port_Init().
**
** Global Variables Used : Port_GblDriverStatus, Port_GpConfigPtr, Port_GpPortPinConfig,
**                         Port_TypeInformation
**
** Functions Invoked     : Det_ReportError,
**                         Port_SwitchSetting
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_002, PORT_DUD_ACT_002_ERR001,
** Reference ID          : PORT_DUD_ACT_002_ERR002, PORT_DUD_ACT_002_ERR003,
** Reference ID          : PORT_DUD_ACT_002_ERR004
***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)                    /* PRQA S 1503 # JV-01 */
{
  P2CONST(Port_Info, AUTOMATIC, PORT_CONFIG_CONST) LpPortInfo;
  Std_ReturnType LucResult;
  uint16 LusPortType;
  uint16 LusPortLoc;
  uint16 LusBitLoc;
  uint8 LucPinMode;

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
 /* Get core id for the current branching */
  LucCoreId = PORT_ONE << (uint8)GetCoreID();
  #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

  LucResult = E_OK;

  /* Check whether the PORT module is Initialized */
  if (PORT_UNINITIALIZED == Port_GblDriverStatus)                                                                     /* PRQA S 3416 # JV-01 */
  {
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_UNINIT);
    #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
    /* Set Return Value as E_NOT_OK */
    LucResult = E_NOT_OK;
  }
  else
  {
    #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
    if ((Port_GpPortPinConfig[Pin].ucPortPinCoreIndex & LucCoreId) != LucCoreId)                                      /* PRQA S 3416 # JV-01 */
    {
      /* Report to DET */
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_INVALID_CORE);
      #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
      /* Set Return Value as E_NOT_OK */
      LucResult = E_NOT_OK;
    }
    else
    #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */
    {
      /* Check whether the requested PIN number is invalid */
      if (Pin >= Port_GpConfigPtr->ulUsePinNumber)                                                                    /* PRQA S 3416 # JV-01 */
      {
        #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_PARAM_PIN);
        #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
        /* Set Return Value as E_NOT_OK */
        LucResult = E_NOT_OK;
      }
      else
      {
        /* Check whether any Pin direction changeable exist */
        if (PORT_CHG_DIRECTION != (uint16)(Port_GpPortPinConfig[Pin].usChangeable & PORT_CHG_DIRECTION))              /* PRQA S 3416 # JV-01 */
        {
          #if (PORT_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_DIRECTION_UNCHANGEABLE);
          #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
          /* Set Return Value as E_NOT_OK */
          LucResult = E_NOT_OK;
        } /* Else No action required */
      }
    }
  }

  if (E_OK == LucResult)
  {
    LusPortType = Port_GpPortPinConfig[Pin].usPortType;
    LusPortLoc = Port_GpPortPinConfig[Pin].usPortLoc;
    LusBitLoc = Port_GpPortPinConfig[Pin].usBitLoc;
    /* Set Port Information Address */
    LpPortInfo = &(Port_TypeInformation[LusPortType].pPortInfo[LusPortLoc]);

    /* Set Direction of pin (LucPinMode: PORT_DEFAULT for PORT; JPORT and PORT_MODE_DIO for Pin 
       which does not support PMC reigster (included APORT) */
    if (LusBitLoc == (LpPortInfo->stRegInfo[PORT_REG_PMC].usValid & LusBitLoc))
    {
      LucPinMode = (uint8)PORT_DEFAULT;                                                                                 /* PRQA S 2905 # JV-01 */
    }
    else
    {
      LucPinMode = (uint8)PORT_MODE_DIO;
    }

    Port_SwitchSetting(LusPortType, LusPortLoc, LusBitLoc, Direction, LucPinMode);
  } /* Else no action required */
  
} /* End of API Port_SetPinDirection */

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
#endif /* (PORT_SET_PIN_DIRECTION_API == STD_ON) */

#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_RefreshPortDirection
**
** Service ID            : 0x02
**
** Description           : This service shall refresh the direction of all
**                         configured ports to the configured direction.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Ports should be initialized by calling Port_init().
**
** Global Variables Used : Port_GblDriverStatus, Port_GpConfigPtr, Port_GpPortPinConfig,
**                         Port_TypeInformation, Port_GpPortConfig.
**
** Functions Invoked     : Det_ReportError, Port_SwitchSetting16.
**                         SchM_Enter_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL(),
**                         SchM_Exit_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL()
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_003, PORT_DUD_ACT_003_ERR001,
** Reference ID          : PORT_DUD_ACT_003_ERR002,
** Reference ID          : PORT_DUD_ACT_003_CRT002, PORT_DUD_ACT_003_CRT001
***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_RefreshPortDirection(void)                                                            /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucResult;
  uint32 LulPinCnt;
  uint16 LusPortType;
  uint16 LusPortLoc;
  uint16 LusBitLoc;
  P2CONST(Port_Pin_Config, AUTOMATIC, PORT_CONFIG_CONST) LpPinConfig;
  P2CONST(Port_Reg_Init, AUTOMATIC, PORT_CONFIG_CONST) LpRegInit;
  P2CONST(Port_Info, AUTOMATIC, PORT_CONFIG_CONST) LpPortInfo;

  uint16 LusRefresh[PORT_TYPE_NUM][PORT_MAX_NUM];
  uint16 LusPMInit[PORT_TYPE_NUM][PORT_MAX_NUM];
  uint16 LusPIBCInit[PORT_TYPE_NUM][PORT_MAX_NUM];

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

  LucResult = E_OK;

  /* Check whether the PORT module is initialized */
  if (PORT_UNINITIALIZED == Port_GblDriverStatus)                                                                     /* PRQA S 3416 # JV-01 */
  {
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET  */
    (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIR_SID, PORT_E_UNINIT);
    #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
    LucResult = E_NOT_OK;
  } /* Else no action required */
  else
  {
    #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
    if ((Port_GpConfigPtr->ucPortKernelCoreId) != LucCoreId)                                                          /* PRQA S 3416 # JV-01 */
    {
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIR_SID, PORT_E_INVALID_CORE);
      #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
      /* Set Result value as E_NOT_OK */
      LucResult = E_NOT_OK;
    } /* Else no action required */
    #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */
  }

  if (E_OK == LucResult)
  {
    /* clear refresh info for Direction */
    for (LusPortType = (uint16)PORT_ZERO; LusPortType < PORT_TYPE_NUM; LusPortType++)
    {
      for (LusPortLoc = (uint16)PORT_ZERO; LusPortLoc < PORT_MAX_NUM; LusPortLoc++)
      {
        LusRefresh[LusPortType][LusPortLoc] = (uint16)PORT_ZERO;
        LusPMInit[LusPortType][LusPortLoc] = (uint16)PORT_ZERO;
        LusPIBCInit[LusPortType][LusPortLoc] = (uint16)PORT_ZERO;
      }
    }

    /* set refresh info for Direction */
    for (LulPinCnt = (uint32)PORT_ZERO; (LulPinCnt < Port_GpConfigPtr->ulUsePinNumber) && (E_OK == LucResult);          /* PRQA S 3416, 2995 # JV-01, JV-01 */
         LulPinCnt++)
    {
      /* not changeable for Direction */
      LpPinConfig = &(Port_GpPortPinConfig[LulPinCnt]);
      if (PORT_CHG_DIRECTION != (uint16)(LpPinConfig->usChangeable & PORT_CHG_DIRECTION))
      {
        LusPortType = LpPinConfig->usPortType;
        LusPortLoc = LpPinConfig->usPortLoc;
        LusBitLoc = LpPinConfig->usBitLoc;
        /* Set Port Information Address */
        LpPortInfo = &(Port_TypeInformation[LusPortType].pPortInfo[LusPortLoc]);

        if (LusBitLoc == (LpPortInfo->stRegInfo[PORT_REG_PM].usValid & LusBitLoc))
        {
          LusRefresh[LusPortType][LusPortLoc] |= LusBitLoc;
          LpRegInit = Port_GpPortConfig[LusPortType];
          LusPMInit[LusPortType][LusPortLoc] |= (LpRegInit[LusPortLoc].usPortRegInit[PORT_REG_PM] & LusBitLoc);
          LusPIBCInit[LusPortType][LusPortLoc] |= (LpRegInit[LusPortLoc].usPortRegInit[PORT_REG_PIBC] & LusBitLoc);
        } /* Else no action required */
      } /* Else No action required */
    }
    /* Enter critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_ENTER_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/

    for (LusPortType = (uint16)PORT_ZERO; LusPortType < PORT_TYPE_NUM; LusPortType++)
    {
      for (LusPortLoc = (uint16)PORT_ZERO; LusPortLoc < Port_TypeInformation[LusPortType].usPortNum; LusPortLoc++)
      {
        /* refresh direction */
        if ((uint16)PORT_ZERO != LusRefresh[LusPortType][LusPortLoc])
        {
          /* Set Direction of Port */
          Port_SwitchSetting16(LusPortType, LusPortLoc, LusRefresh[LusPortType][LusPortLoc],
                                          LusPMInit[LusPortType][LusPortLoc], LusPIBCInit[LusPortType][LusPortLoc]);
        } /* Else no action required */

      }
    }
    /* Exit critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_EXIT_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/
  } /* Else no action required */
  
} /* End of API Port_RefreshPortDirection */

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */

#if (PORT_VERSION_INFO_API == STD_ON)
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_GetVersionInfo
**
** Service ID            : 0x03
**
** Description           : This API returns the version information of PORT
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
** Reference ID          : PORT_DUD_ACT_004, PORT_DUD_ACT_004_ERR001
***********************************************************************************************************************/

FUNC(void, PORT_PUBLIC_CODE) Port_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versioninfo)     /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
    versioninfo->moduleID = (uint16)PORT_MODULE_ID;
    versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
  }
}

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
#endif /* (PORT_VERSION_INFO_API == STD_ON) */

#if (PORT_SET_PIN_MODE_API == STD_ON)
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_SetPinMode
**
** Service ID            : 0x04
**
** Description           : This function used to set the mode of a port pin
**                         during runtime.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Pin - Port Pin ID number
**                         Mode - New mode to be set on port pin.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Ports should be initialized by calling Port_init().
**
** Global Variables Used : Port_GblDriverStatus, Port_GpConfigPtr, Port_GpPortPinConfig
**
** Functions Invoked     : Det_ReportError,
**                         Port_SetPweMode,
**                         Port_ResetMode,
**                         Port_SetMode,
**                         SchM_Enter_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL(),
**                         SchM_Exit_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL()
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_005, PORT_DUD_ACT_005_ERR001,
** Reference ID          : PORT_DUD_ACT_005_ERR002, PORT_DUD_ACT_005_ERR003,
** Reference ID          : PORT_DUD_ACT_005_ERR004, PORT_DUD_ACT_005_ERR005,
** Reference ID          : PORT_DUD_ACT_005_ERR006, PORT_DUD_ACT_005_ERR007 
** Reference ID          : PORT_DUD_ACT_005_CRT001, PORT_DUD_ACT_005_CRT002
** Reference ID          : PORT_DUD_ACT_005_CRT003, PORT_DUD_ACT_005_CRT004
***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)                                   /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucResult;
  uint16 LusPortType;
  uint16 LusPortLoc;
  uint16 LusBitLoc;

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
 /* Get core id for the current branching */
  LucCoreId = PORT_ONE << (uint8)GetCoreID();
  #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

  LucResult = E_OK;

  /* Check whether the PORT module is initialized */
  if (PORT_UNINITIALIZED == Port_GblDriverStatus)                                                                     /* PRQA S 3416 # JV-01 */
  {
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
    #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
    /* Set Return Value as E_NOT_OK */
    LucResult = E_NOT_OK;
  } /* Port_GblDriverStatus == PORT_UNINITIALIZED */
  else
  {
    #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
    if ((Port_GpPortPinConfig[Pin].ucPortPinCoreIndex & LucCoreId) != LucCoreId)                                      /* PRQA S 3416 # JV-01 */
    {
      /* Report to DET */
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_INVALID_CORE);
      #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
      /* Set Return Value as E_NOT_OK */
      LucResult = E_NOT_OK;
    }
    else
    #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */
    {
      /* Parameter Error for Pin number */
      if (Pin >= Port_GpConfigPtr->ulUsePinNumber)                                                                    /* PRQA S 3416 # JV-01 */
      {
        #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
        LucResult = E_NOT_OK;
      }
      else
      {
        /* not changeable Mode */
        if (PORT_CHG_MODE != (uint16)(Port_GpPortPinConfig[Pin].usChangeable & PORT_CHG_MODE))                        /* PRQA S 3416 # JV-01 */
        {
          #if (PORT_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
          #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
          LucResult = E_NOT_OK;
        } /* Else No action required */
        /* not available mode*/
        if ((PORT_DEFAULT != Mode) && ((uint32)PORT_MODE_DIO_OUT != Mode) && ((uint32)PORT_MODE_DIO_IN != Mode) && 
            (PORT_BYTE_ZERO == (uint16)(Port_GpPortPinConfig[Pin].usModeAvailable &                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
          ((uint16)(PORT_BYTE_ONE << ((uint16)(Mode >> PORT_FOUR)))))))
        {
          #if (PORT_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
          #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
          LucResult = E_NOT_OK;
        }
        else
        {
          if ((PORT_DEFAULT != Mode) && ((uint32)PORT_MODE_DIO_OUT != Mode) && ((uint32)PORT_MODE_DIO_IN != Mode) &&
              ((uint32)PORT_MODE_ALT_OUT == (Mode & (uint32)PORT_ALT_MODE_MASK)))
          {
            if (PORT_BYTE_ZERO == (uint16)(Port_GpPortPinConfig[Pin].usModeDirOut &                                     /* PRQA S 3416 # JV-01 */
              ((uint16)(PORT_BYTE_ONE << ((uint16)(Mode >> PORT_FOUR))))))
            {
              #if (PORT_DEV_ERROR_DETECT == STD_ON)
              /* Report to DET */
              (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
              #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
              LucResult = E_NOT_OK;
            } 
          }
          else if ((PORT_DEFAULT != Mode) && ((uint32)PORT_MODE_DIO_OUT != Mode) && ((uint32)PORT_MODE_DIO_IN != Mode)  /* PRQA S 2004 # JV-01 */
                && ((uint32)PORT_MODE_ALT_IN == (Mode & (uint32)PORT_ALT_MODE_MASK)))
          {
            if (PORT_BYTE_ZERO == (uint16)(Port_GpPortPinConfig[Pin].usModeDirIn &                                      /* PRQA S 3416 # JV-01 */
              ((uint16)(PORT_BYTE_ONE << ((uint16)(Mode >> PORT_FOUR))))))
            {
              #if (PORT_DEV_ERROR_DETECT == STD_ON)
              /* Report to DET */
              (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
              #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
              LucResult = E_NOT_OK;
            }
          }
        }
      }
    }
  }
  
  if (E_OK == LucResult)
  {
    LusPortType = Port_GpPortPinConfig[Pin].usPortType;
    LusPortLoc = Port_GpPortPinConfig[Pin].usPortLoc;
    LusBitLoc = Port_GpPortPinConfig[Pin].usBitLoc;
    /* Enter critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_ENTER_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/

    /* Set Enable to  PWE */
    Port_SetPweMode(LusPortType, LusPortLoc, PORT_ENABLE);

    /* Exit critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_EXIT_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/

    /* Reset mode */
    Port_ResetMode(LusPortType, LusPortLoc, LusBitLoc);

    /* Set mode */
    (void)Port_SetMode(LusPortType, LusPortLoc, LusBitLoc, Mode);

    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_ENTER_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/

    /* Set Disable to  PWE */
    Port_SetPweMode(LusPortType, LusPortLoc, PORT_DISABLE);

    /* Exit critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_EXIT_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/
  } /* Else no action required */
  
} /* End of API Port_SetPinMode */

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
#endif /* PORT_SET_PIN_MODE_API == STD_ON */

#if (PORT_SET_TO_DIO_ALT_MODE_API == STD_ON)
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_SetToDioMode
**
** Service ID            : 0x05
**
** Description           : This function used to set the mode of a port pin
**                         to DIO mode during runtime.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddPinNumber - Port Pin ID number
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Ports should be initialized by calling Port_init().
**
** Global Variables Used : None
**
** Functions Invoked     : Port_SetDioAltMode.
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_006
***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_SetToDioMode(const Port_PinType LddPinNumber)                                         /* PRQA S 1503 # JV-01 */
{
  /* Set DIO mode */
  Port_SetDioAltMode(LddPinNumber, (uint8)PORT_MODE_DIO, PORT_SET_TO_DIO_MODE_SID);
} /* End of API Port_SetToDioMode */

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
#endif /* PORT_SET_TO_DIO_ALT_MODE_API = = STD_ON */

#if (PORT_SET_TO_DIO_ALT_MODE_API == STD_ON)
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_SetToAlternateMode
**
** Service ID            : 0x06
**
** Description           : This function used to set the mode of a port pin
**                         to alternate mode during runtime.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddPinNumber - Port Pin ID number
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Ports should be initialized by calling Port_init().
**
** Global Variables Used : None
**
** Functions Invoked     : Port_SetDioAltMode.
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_007
***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_SetToAlternateMode(const Port_PinType LddPinNumber)                                   /* PRQA S 1503 # JV-01 */
{
  Port_SetDioAltMode(LddPinNumber, (uint8)PORT_MODE_ALT, PORT_SET_TO_ALT_MODE_SID);
} /* End of API Port_SetToAlternateMode */

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
#endif /* PORT_SET_TO_DIO_ALT_MODE_API = = STD_ON */

#if ((PORT_SET_PIN_DEFAULT_DIRECTION_API == STD_ON) && (PORT_SET_PIN_DIRECTION_API == STD_ON))
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_SetPinDefaultDirection
**
** Service ID            : 0x08
**
** Description           : This service sets the port pin direction during
**                         runtime. The PORT Driver module allows changing the
**                         mode of the pin to default mode set by the
**                         configuration at the time of Port_Init().
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddPinNumber - Port Pin ID number
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Ports should be  initialized by calling Port_Init().
**                         Port_SetPinDirection() should be invoked during
**                         runtime.
**
** Global Variables Used : Port_GblDriverStatus, Port_GpConfigPtr, Port_TypeInformation, Port_GpPortConfig,
**                         Port_GpPortPinConfig.
**
** Functions Invoked     : Det_ReportError,
**                         Port_SwitchSetting
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_009, PORT_DUD_ACT_009_ERR001,
** Reference ID          : PORT_DUD_ACT_009_ERR002, PORT_DUD_ACT_009_ERR003
** Reference ID          : PORT_DUD_ACT_009_ERR004

***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDefaultDirection(const Port_PinType LddPinNumber)                               /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucResult;
  uint16 LusPortType;
  uint16 LusPortLoc;
  uint16 LusBitLoc;
  uint8 LucPinMode;
  P2CONST(Port_Info, AUTOMATIC, PORT_CONFIG_CONST) LpPortInfo;
  P2CONST(Port_Reg_Init, AUTOMATIC, PORT_CONFIG_DATA) LpRegInit;
  Port_PinDirectionType LenDirection;

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for the current branching */
  LucCoreId = PORT_ONE << (uint8)GetCoreID();
  #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

  LucResult = E_OK;

  /* Check whether the PORT module is initialized */
  if (PORT_UNINITIALIZED == Port_GblDriverStatus)                                                                     /* PRQA S 3416 # JV-01 */
  {
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DEFAULT_DIR_SID, PORT_E_UNINIT);
    /* Set Return Value as E_NOT_OK */
    #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
    LucResult = E_NOT_OK;
  }
  else
  {
    #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
    if ((Port_GpPortPinConfig[LddPinNumber].ucPortPinCoreIndex & LucCoreId) != LucCoreId)                             /* PRQA S 3416 # JV-01 */
    {
      /* Report to DET */
      #if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DEFAULT_DIR_SID, PORT_E_INVALID_CORE);
      #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
      /* Set Return Value as E_NOT_OK */
      LucResult = E_NOT_OK;
    }
    else
    #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */
    {
      /* Parameter Error for Pin number */
      if (LddPinNumber >= Port_GpConfigPtr->ulUsePinNumber)                                                           /* PRQA S 3416 # JV-01 */
      {
        #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DEFAULT_DIR_SID, PORT_E_PARAM_PIN);
        #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
        LucResult = E_NOT_OK;
      }
      else
      {
        /* not changeable direction */
        if (PORT_CHG_DIRECTION != (uint16)(Port_GpPortPinConfig[LddPinNumber].usChangeable & PORT_CHG_DIRECTION))     /* PRQA S 3416 # JV-01 */
        {
          #if (PORT_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DEFAULT_DIR_SID,
                                PORT_E_DIRECTION_UNCHANGEABLE);
          #endif /* End of PORT_DEV_ERROR_DETECT == STD_ON */
          LucResult = E_NOT_OK;
        } /* Else no action required */
      }
    }
  }

  if (E_OK == LucResult)
  {
    LusPortType = Port_GpPortPinConfig[LddPinNumber].usPortType;
    LusPortLoc = Port_GpPortPinConfig[LddPinNumber].usPortLoc;
    LusBitLoc = Port_GpPortPinConfig[LddPinNumber].usBitLoc;
    /* Set Port Information Address */
    LpPortInfo = &(Port_TypeInformation[LusPortType].pPortInfo[LusPortLoc]);

    LpRegInit = Port_GpPortConfig[LusPortType];
    if (LusBitLoc == (LpRegInit[LusPortLoc].usPortRegInit[PORT_REG_PM] & LusBitLoc))
    {
      LenDirection = PORT_PIN_IN;
    }
    else
    {
      LenDirection = PORT_PIN_OUT;
    }

    /* Check if port pin does not support PMC register (included ANALOG port), set mode to PORT_MODE_DIO */
    if (LusBitLoc == (LpPortInfo->stRegInfo[PORT_REG_PMC].usValid & LusBitLoc))
    {
      LucPinMode = (uint8)PORT_DEFAULT;                                                                                 /* PRQA S 2905 # JV-01 */
    }
    else
    {
      LucPinMode = (uint8)PORT_MODE_DIO;
    }

    Port_SwitchSetting(LusPortType, LusPortLoc, LusBitLoc, LenDirection, LucPinMode);
  } /* Else No action required */

} /* End of API Port_SetPinDefaultDirection */

#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
#endif /* (PORT_SET_PIN_DEFAULT_DIRECTION_API == STD_ON) */

#if (PORT_ECM_ERRORIN_API == STD_ON)
#define PORT_START_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_EcmMaskERRORIN
**
** Service ID            : 0x09
**
** Description           : This service sets the Mask/Unmask the ECM error
**                         output signal of ERRORIN.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LblMask - Mask/Unmask
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : boolean
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Port_MaskECM
**                         SchM_Enter_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL(),
**                         SchM_Exit_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL()
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_010, PORT_DUD_ACT_010_CRT001,
** Reference ID          : PORT_DUD_ACT_010_CRT002
***********************************************************************************************************************/
FUNC(boolean, PORT_PUBLIC_CODE) Port_EcmMaskERRORIN(const boolean LblMask)                                              /* PRQA S 1503 # JV-01 */
{
  boolean LblERRORIN;

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  LblERRORIN = PORT_UNMASK;
  if ((Port_GpConfigPtr->ucPortKernelCoreId) == LucCoreId)                                                              /* PRQA S 3416 # JV-01 */
  #endif /* #if (PORT_MUTLI_CORE_SUPPORT == STD_ON) */
  {
    /* Enter critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_ENTER_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/

    /* Mask/Unmask the ECM error output signal of ERRORIN. */
    LblERRORIN = Port_MaskECM(LblMask);

    /* Exit critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_EXIT_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/
  }

  return LblERRORIN;
}

/***********************************************************************************************************************
** Function Name         : Port_EcmClearERRORIN
**
** Service ID            : 0x0A
**
** Description           : This service clear the ECM error status of ERRORIN.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Port_ClearECM
**                         SchM_Enter_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL(),
**                         SchM_Exit_Port_PORT_INTERRUPT_CONTROL_PROTECTION_INTER_GLOBAL()
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_011, PORT_DUD_ACT_011_CRT001,
** Reference ID          : PORT_DUD_ACT_011_CRT002
***********************************************************************************************************************/
FUNC(void, PORT_PUBLIC_CODE) Port_EcmClearERRORIN(void)                                                                 /* PRQA S 1503 # JV-01 */
{
  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  if ((Port_GpConfigPtr->ucPortKernelCoreId) == LucCoreId)                                                              /* PRQA S 3416 # JV-01 */
  #endif /* #if (PORT_MUTLI_CORE_SUPPORT == STD_ON) */
  {
    /* Enter critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_ENTER_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/

    /* Clear the ECM error status of ERRORIN */
    Port_ClearECM();

    /* Exit critical section */
    #if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
    PORT_EXIT_CRITICAL_SECTION(PORT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif /* End of CRITICAL_SECTION_PROTECTION == STD_ON*/
  }
}
#define PORT_STOP_SEC_PUBLIC_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
#endif /* (PORT_ECM_ERRORIN_API == STD_ON) */

#define PORT_START_SEC_PRIVATE_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Port_SetStatus
**
** Service ID            : None
**
** Description           : This service sets the status of Port_GblDriverStatus
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LblStatus - Port Status
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Port_GblDriverStatus
**
** Functions Invoked     : None
**
** Registers Used        : None
**
** Reference ID          : PORT_DUD_ACT_012, PORT_DUD_ACT_012_GBL001
***********************************************************************************************************************/
STATIC FUNC(void, PORT_PRIVATE_CODE) Port_SetStatus(const boolean LblStatus)
{
  Port_GblDriverStatus = LblStatus;
}
#define PORT_STOP_SEC_PRIVATE_CODE
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
