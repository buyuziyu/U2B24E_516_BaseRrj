/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of ADC Driver Component                                                               */
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
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : As part of ARDAACL-49170 support, following changes are made:
 *                     1.Update Sync/Async of Adc_EnableHardwareTrigger, Adc_DisableHardwareTrigger to Asynchronous
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.1.1: 22/08/2024 : As part of U2Bx-E support, following changes are made:
 *                     1.Add Adc_GpTnHChannelSelectValue into API function Adc_Init
 *                     As part of Multicore support, following changes are made:
 *                     1.Update to change ADC_KERNEL_COREID macro to global variable Adc_GucCoreIndex
 *                     2.Update to change ADC_MAX_SW_TRIGGER macro to global variable Adc_GucMaxSwTriggGroups
 *                     3.Update to change Sync to Async information for functions Adc_EnableHardwareTrigger and
 *                     Adc_DisableHardwareTrigger
 * 2.0.1: 12/10/2023 : Support Autosar R22-11
 *                     1. Change macro ADC_AR_R21_11_VERSION to ADC_AR_R22_11_VERSION support Autosar version.
 *                     2. In API function Adc_SetupResultBuffer(), move the condition of checking DET error
 *                        Adc_GblDriverStatus is performed first.
 * 2.0.0: 28/08/2023 : Support Autosar multi-core distribution type IV
                       1. Memory section separate for Global and Local API
                       2. Update Global Critical Section 
                       3. Add DET check for Local API: Adc_Init, Adc_DeInit, Adc_ReadGroup polling mode
                       4. Adc_ReadGroup, Adc_GetStreamLastPointer, Adc_EnableGroupNotification, Adc_GetGroupStatus,
                          SetupResultBuffer, Adc_EnableChannel, Adc_DisableChannel, Adc_DisableGroupNotification:
                          add core Det check will support multi-core same behavior as single core.
                       5. Adc_StartGroupConversion, Adc_StopGroupConversion, Adc_EnableHardwareTrigger, 
                          Adc_DisableHardwareTrigger: Add DET check, separate code for multi-core and single-core,
                          master core using master satellite concept, single core same as previous implementation
                       6. Remove multi-instances define, Update Adc_Mapping.h to Adc_Memmap.h 
 *        11/06/2023 : Change macro ADC_AR_2111_VERSION to ADC_AR_R21_11_VERSION support Autosar version.  
 * 1.5.0: 19/04/2023 : Added the ADC_AR_2111_VERSION compile switch area
 * 1.4.5: 15/09/2022 : Updated QAC messages according to QAC analysis results.
 *        12/09/2022 : Replaced the empty else blocks, not from else if, with comments.
 *                     Removed empty if blocks between compilation switches as else blocks by inverting the condition.
 *                     Separated each bit of ucGroupSettings into independent variables.
 *                     Fixed comments about 'end of'.
 * 1.4.4: 24/08/2022 : Updated information in function header comments.
 *        21/07/2022 : Moved status checks and transitions, DEM error reporting, and critical section containing them
 *                     in the function Adc_StopGroupConversion to the internal function.
 *                     Updated Global Variables, Functions invoked, and Reference IDs in function header comments.
 *        20/06/2022 : Added a copy of pHwTriggConfig and removed copies of pHWGroupTrigg and pSGGroupTrigg in Adc_Init.
 * 1.4.3: 23/05/2022 : Updated QAC messages for U2Bx.
 *        18/05/2022 : Changed the filename of the SchM_Adc header to macro for multi-instances.
 *                     Fixed the typos in comments.
 *        15/04/2022 : Changed the pointers to the HW trigger configuration to the new structure for U2Bx.
 * 1.4.1: 25/11/2021 : Changed the condition of compile switch to support ADCK.
 * 1.3.2: 06/09/2021 : Changed to Adc_Mapping.h from Adc_MemMap.h
 *        03/09/2021 : Added copying supplementary information when PWM-Diag.
 *        18/07/2021 : Moved the database validation into the ADC_DEV_ERROR_DETECT compile switch area.
 * 1.3.1: 17/07/2021 : Added the CONST qualifier to pointers that have not changed their reference.
 *        08/07/2021 : Changed the name of the global variable Adc_GpWaitTimeConfig to conform to Camel.
 *                     Integrated the ADC_DET_REPORT_ERROR_NOFLAG and ADC_DET_REPORT_ERROR into ADC_DET_RUNTIME_ERROR.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        16/06/2021 : Added the required cast to a conditional expression.
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        24/05/2021 : Removed unnecessary include header.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 20/01/2021 : Function Adc_SetupResultBuffer, update data type of
 *                     parameter DataBufferPtr from P2CONST to P2VAR.
 *                     Update parameter LddGroup to Group.
 *        06/12/2020 : Initialize new global variable
 *                     Adc_GpTriggOutConfigRegister in function Adc_Init()
 *        05/12/2020 : Report DEM error ADC_E_TIMEOUT in Adc_StopGroupConversion
 *                     in case cannot stop scan group or DMA channel
 *        04/09/2020 : Remove DET check for invalid channel parameter in
 *                     Adc_DisableChannel
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020 : Release
 * 1.0.4: 03/06/2020 : Function Adc_Init: Return without any action after raising
 *                     development error ADC_E_ALREADY_INITIALIZED
 * 1.0.3: 12/05/2020 : Update macro DET_REPORT_ERROR to ADC_DET_REPORT_ERROR
 * 1.0.2: 28/04/2020 : Report ADC_E_BUSY while requested group is present in the
 *                     queue in API Adc_EnableChannel, Adc_DisableChannel.
 * 1.0.1: 13/04/2020 : Update software version definition.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for macro definitions and type definitions */
#include "Adc.h"
#include "Adc_Cfg.h"
#include "Adc_Ram.h"

/* Included for the declaration of internal function prototypes */
#include "Adc_LLDriver.h"

#if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
     (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
           (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */

/* Included for declaration of the function DEM_REPORT_ERROR() */
#include "Dem.h"

#if (ADC_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Adc.h"
#endif /* (ADC_CRITICAL_SECTION_PROTECTION == STD_ON) */

#if (ADC_MULTI_CORE_SUPPORT == STD_ON)
#include "Adc_Kernel.h"
#include "Os.h"
#endif
/*******************************************************--**************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_AR_RELEASE_MAJOR_VERSION != ADC_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc.c : Mismatch in Release Major Version"
#endif

#if (ADC_AR_RELEASE_MINOR_VERSION != ADC_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc.c : Mismatch in Release Minor Version"
#endif

#if (ADC_AR_RELEASE_REVISION_VERSION != ADC_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc.c : Mismatch in Release Revision Version"
#endif

#if (ADC_SW_MAJOR_VERSION != ADC_C_SW_MAJOR_VERSION)
  #error "Adc.c : Mismatch in Software Major Version"
#endif

#if (ADC_SW_MINOR_VERSION != ADC_C_SW_MINOR_VERSION)
  #error "Adc.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127,       */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM EXP08, ARR30, ARR37, ARR38, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125,    */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633, CWE-740              */
/* JV-01 Justification : This message prevents existing of an out-of-range pointer                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : MISRA C:2012 Rule-10.3, CERTCCM INT02, CWE Rule CWE-681, CWE-136, CWE-192                    */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name        : Adc_Init
**
** Service ID           : 0x00
**
** Description          : This API performs the initialization of the ADC Driver component.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : ConfigPtr
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : This function should not be called if the ADC Driver is already initialized.
**
** Global Variables     : Adc_GblDriverStatus, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig, Adc_GpGroupConfig,
**                        Adc_GpHWGroupTrigg, Adc_GpSGGroupTrigg, Adc_GpTriggOutConfigRegister,
**                        Adc_GpTriggOutConfigValue, Adc_GpChannelToGroup, Adc_GpHwUnitIndex, Adc_GpSgUnitIndex,
**                        Adc_GpLimitCheckRange, Adc_GpGroupRamData, Adc_GpSgUnitRamData, Adc_GucMaxSwTriggGroups,
**                        Adc_GucNoOfGroups, Adc_GpChannelToDisableEnable, Adc_GpDmaHWUnitMapping,
**                        Adc_GpDmaUnitConfig, Adc_GpDmaSGUnitMapping, Adc_GucMaxDmaChannels, Adc_GpWaitTimeConfig,
**                        Adc_GpHwTriggConfig, Adc_GucCoreIndex, Adc_GpTnHChannelSelectValue
**
** Functions invoked    : Det_ReportError, Adc_HwInit
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_001, ADC_DUD_ACT_001_ERR001, ADC_DUD_ACT_001_ERR002,
** Reference ID         : ADC_DUD_ACT_001_ERR003, ADC_DUD_ACT_001_ERR004, ADC_DUD_ACT_001_GBL001,
** Reference ID         : ADC_DUD_ACT_001_GBL002, ADC_DUD_ACT_001_GBL003, ADC_DUD_ACT_001_GBL004,
** Reference ID         : ADC_DUD_ACT_001_GBL005, ADC_DUD_ACT_001_GBL006, ADC_DUD_ACT_001_GBL007,
** Reference ID         : ADC_DUD_ACT_001_GBL008, ADC_DUD_ACT_001_GBL009, ADC_DUD_ACT_001_GBL010,
** Reference ID         : ADC_DUD_ACT_001_GBL011, ADC_DUD_ACT_001_GBL012, ADC_DUD_ACT_001_GBL013,
** Reference ID         : ADC_DUD_ACT_001_GBL014, ADC_DUD_ACT_001_GBL015, ADC_DUD_ACT_001_GBL016,
** Reference ID         : ADC_DUD_ACT_001_GBL017, ADC_DUD_ACT_001_GBL018, ADC_DUD_ACT_001_GBL019
***********************************************************************************************************************/
#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"

FUNC(void, ADC_PUBLIC_CODE) Adc_Init(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_CONFIG_DATA) ConfigPtr)                     /* PRQA S 1503 # JV-01 */
{
  #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
  uint8 LucNoChannelInGroup;
  uint8 LucLoopCount;
  #endif
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;

  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */

  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;

  #if (ADC_ALREADY_INIT_DET_CHECK == STD_ON)
  /* Check if the ADC Driver is already initialized */
  if (ADC_INITIALIZED == Adc_GblDriverStatus)                                                                           /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_INIT_SID, ADC_E_ALREADY_INITIALIZED);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  else
  #endif /* (ADC_ALREADY_INIT_DET_CHECK == STD_ON) */
  {
    /* Check if the Configuration pointer is NULL */
    if (NULL_PTR == ConfigPtr)
    {
      /* Report Error to DET */
      #if (ADC_AR_VERSION == ADC_AR_422_VERSION)
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_INIT_SID, ADC_E_PARAM_CONFIG);
      #elif ((ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_INIT_SID, ADC_E_PARAM_POINTER);
      #endif /* (ADC_AR_VERSION == ADC_AR_422_VERSION) */
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    }
    /* Check if database is invalid */
    else 
    {
      if (ADC_DBTOC_VALUE != ConfigPtr->ulStartOfDbToc)
      {
        /* Report Error to DET */
        (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_INIT_SID, ADC_E_INVALID_DATABASE);
        /* Set the error status flag to ADC_TRUE */
        LblDetErrFlag = ADC_TRUE;
      }
      else
      {
        #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
        /* Check if control API wasn't executed on Master Core */
        if (LucCoreID != ConfigPtr->ucCoreIndex)                                                                        /* PRQA S 3416 # JV-01 */
        {
          /* Report Error to DET */
          (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_INIT_SID, ADC_E_INVALID_CORE);
          LblDetErrFlag = ADC_TRUE;
        }
        #endif /* ADC_MULTI_CORE_SUPPORT */
      }
    }
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize all the global pointers */
    Adc_GpHwUnitConfig = (P2CONST(Adc_HwUnitConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pHWUnitConfig;     /* PRQA S 0316, 2814 # JV-01, JV-01 */
    Adc_GpSgUnitConfig = (P2CONST(Adc_HwSgUnitType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pSgUnitConfig;         /* PRQA S 0316 # JV-01 */
    Adc_GpGroupConfig = (P2CONST(Adc_GroupConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pGroupConfig;        /* PRQA S 0316 # JV-01 */
    #if (ADC_ENABLE_PIC_TSEL == STD_ON)
    #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
    Adc_GpHwTriggConfig =
      (P2CONST(Adc_HwTriggConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pHwTriggConfig;                      /* PRQA S 0316 # JV-01 */
    #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
    #if (ADC_IP_ADCH == STD_ON)
    Adc_GpHWGroupTrigg = (P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pGroupHWTrigg;
    Adc_GpSGGroupTrigg = (P2CONST(Adc_PicConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pGroupSGTrigg;
    Adc_GpTriggOutConfigRegister =
      (P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pTriggOutConfigRegister;
    Adc_GpTriggOutConfigValue = (P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pTriggOutConfigValue;
    #endif /* (ADC_IP_ADCH == STD_ON) */
    #endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */
    Adc_GpChannelToGroup = (P2CONST(uint32, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pChannelToGroup;               /* PRQA S 0316 # JV-01 */
    Adc_GpHwUnitIndex = (P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pHwUnitIndex;                      /* PRQA S 0316 # JV-01 */
    Adc_GpSgUnitIndex = (P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pSgUnitIndex;                      /* PRQA S 0316 # JV-01 */
    #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    Adc_GpLimitCheckRange =
      (P2CONST(Adc_LimitCheckConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pLimitCheckRange;                 /* PRQA S 0316 # JV-01 */
    #endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
    Adc_GpGroupRamData =
      (P2VAR(volatile Adc_ChannelGroupRamData, ADC_VAR_NO_INIT, ADC_VAR_NO_INIT))ConfigPtr->pGroupRamData;              /* PRQA S 0316 # JV-01 */
    Adc_GpSgUnitRamData =
      (P2VAR(volatile Adc_SgUnitRamData, ADC_VAR_NO_INIT, ADC_VAR_NO_INIT))ConfigPtr->pSgUnitRamData;                   /* PRQA S 0316 # JV-01 */
    Adc_GucMaxSwTriggGroups = ConfigPtr->ucMaxSwTriggGroups;
    Adc_GucNoOfGroups = ConfigPtr->ucNoOfGroups;

    #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
    Adc_GpChannelToDisableEnable =
      (P2VAR(volatile boolean, ADC_VAR_NO_INIT, ADC_VAR_NO_INIT))ConfigPtr->pChannelToDisableEnable;                    /* PRQA S 0316 # JV-01 */
    LucNoChannelInGroup = ConfigPtr->ucNoOfChannels;
    /* Make all the channel enable for conversion */
    for (LucLoopCount = ADC_VAL_BYTE_INIT; LucLoopCount < LucNoChannelInGroup; LucLoopCount++)
    {
      Adc_GpChannelToDisableEnable[LucLoopCount] = ADC_TRUE;                                                            /* PRQA S 2824 # JV-01 */
    }
    #endif /* (ADC_ENABLE_DISABLE_CHANNEL == STD_ON) */

    #if (ADC_ENABLE_DMA_MODE == STD_ON)
    /* Initialize the global pointer for DMA channel and HW unit mapping */
    Adc_GpDmaHWUnitMapping = (P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pDmaHWUnitMapping;            /* PRQA S 0316 # JV-01 */
    /* Pointer to DMA channel configuration */
    Adc_GpDmaUnitConfig = (P2CONST(Adc_DmaConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pDmaUnitConfig;      /* PRQA S 0316 # JV-01 */
    /* Initialize the global pointer for DMA channel and SG unit mapping */
    Adc_GpDmaSGUnitMapping = (P2CONST(uint8, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pDmaSGUnitMapping;            /* PRQA S 0316 # JV-01 */
    Adc_GucMaxDmaChannels = ConfigPtr->ucMaxDmaChannels;
    #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
    /* Initialize the global pointer for Wait time and scan group mapping */
    Adc_GpWaitTimeConfig =
      (P2CONST(Adc_WaitTimeConfigType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pWaittimeConfig;                    /* PRQA S 0316 # JV-01 */
    #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
    /* Assign a ucCoreIndex in ConfigPtr to global variable for core ID */
    Adc_GucCoreIndex = ConfigPtr->ucCoreIndex;
    #endif
    #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
    /* Initialize the global pointer for T&H Channel Select */
    Adc_GpTnHChannelSelectValue = 
       (P2CONST(Adc_TrackHoldChannelValueType, ADC_VAR_NO_INIT, ADC_CONFIG_DATA))ConfigPtr->pTnHChannelSelectValue;     /* PRQA S 0316 # JV-01 */
    #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */
    /* Invoke internal initialization function for ADC HW initialization */
    Adc_HwInit();

    /* Set ADC driver as Initialized */
    Adc_GblDriverStatus = ADC_INITIALIZED;
  } /* end of if (ADC_FALSE == LblDetErrFlag) */
    /* else: */
}

#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DeInit
**
** Service ID           : 0x01
**
** Description          : This API performs the De-Initialization of the
**                        ADC Driver component by making all the registers to
**                        the power on reset state.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus
**
** Functions invoked    : Det_ReportError, Adc_HwDeInit
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_002, ADC_DUD_ACT_002_ERR001
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_DeInit(void)                                                                            /* PRQA S 1503 # JV-01 */
{
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  /* Check if control API wasn't executed on Master Core */
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if the ADC Driver is not already initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DEINIT_SID, ADC_E_UNINIT);
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check if control API wasn't executed on Master Core */
  else if (Adc_GucCoreIndex != LucCoreID)                                                                              /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DEINIT_SID, ADC_E_INVALID_CORE);
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Invoke internal deinitialization function for ADC HW deinitialization */
    Adc_HwDeInit();
  }
  
}

#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_StartGroupConversion
**
** Service ID           : 0x02
**
** Description          : This API service shall start the conversion of
**                        all channels of the requested ADC Channel group.
**                        Depending on the group configuration single-shot or
**                        continuous conversion is started.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GucMaxSwTriggGroups, Adc_GpGroupRamData, 
**                        Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError, Adc_HwStartGroupConversion, ADC_DET_RUNTIME_ERROR, ADC_ENTER_CRITICAL_SECTION
**                        Adc_UnLockedStatus, Adc_LockProcess, ADC_EXIT_CRITICAL_SECTION, Adc_UnLockProcess 
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_003, ADC_DUD_ACT_003_ERR001, ADC_DUD_ACT_003_ERR002,
** Reference ID         : ADC_DUD_ACT_003_ERR003, ADC_DUD_ACT_003_ERR004, ADC_DUD_ACT_003_ERR005
***********************************************************************************************************************/
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_StartGroupConversion(Adc_GroupType Group)                                               /* PRQA S 1503 # JV-01 */
{
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;

  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  
  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;
  
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is HW triggered */
  else if (Group >= Adc_GucMaxSwTriggGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_WRONG_TRIGG_SRC);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if result buffer is initialized for requested group */
  else if (ADC_FALSE == Adc_GpGroupRamData[Group].blBufferStatus)                                                       /* PRQA S 2824 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_BUFFER_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check Group is called in valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  {
    /* No action required */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
         (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
    #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
    if (ADC_TRUE == Adc_GpGroupRamData[Group].blGrpPresent)                                                             /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_BUSY);
    }
    else
    #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
    #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
               (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
    {
      #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
      /* Get the SpinLock */
      ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      /* Set request to master core if the shared buffer is ready - not locked by Satellite */
      if (Adc_UnLockedStatus(Adc_StartGroupConversionInfo[Group].blBufferLock))                                         /* PRQA S 2844, 3432 # JV-01, JV-01 */
      {
        Adc_LockProcess(Adc_StartGroupConversionInfo[Group].blBufferLock);                                              /* PRQA S 2844, 3432 # JV-01, JV-01 */
        /* Release the SpinLock */
        ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        /* Update the request */
        Adc_StartGroupConversionInfo[Group].blSetRequest = ADC_TRUE;                                                    /* PRQA S 2844 # JV-01 */
        /* Release Lock */
        Adc_UnLockProcess(Adc_StartGroupConversionInfo[Group].blBufferLock);                                            /* PRQA S 2844, 3432 # JV-01, JV-01 */
      }
      else
      {
        /* Release Lock */
        ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        /* Report to Development Errors */
       (void)ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_REQUEST_FALSE);
      }
      #else
      /* Start the conversion */
      Adc_HwStartGroupConversion(Group);
      #endif /* (ADC_MULTI_CORE_SUPPORT == STD_ON) */
    }
  } /* end of if (ADC_FALSE == LblDetErrFlag) */
    /* else: No action required */
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_StopGroupConversion
**
** Service ID           : 0x03
**
** Description          : This API service shall stop conversion of the
**                        requested ADC Channel group.
**
** Sync/Async           : Single core synchonous and multi core Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GucMaxSwTriggGroups, Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError, Adc_HwStopGroupConversion, ADC_ENTER_CRITICAL_SECTION, Adc_UnLockedStatus,
**                        Adc_LockProcess, ADC_EXIT_CRITICAL_SECTION, Adc_UnLockProcess, ADC_DET_RUNTIME_ERROR
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_004, ADC_DUD_ACT_004_ERR001, ADC_DUD_ACT_004_ERR002, ADC_DUD_ACT_004_ERR003
***********************************************************************************************************************/
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_StopGroupConversion(Adc_GroupType Group)                                                /* PRQA S 1503 # JV-01 */
{
  #if (ADC_DEV_ERROR_DETECT == STD_ON) 
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION_SID, ADC_E_UNINIT);
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION_SID, ADC_E_PARAM_GROUP);
  }
  /* Check if the requested group is HW triggered */
  else if (Group >= Adc_GucMaxSwTriggGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION_SID, ADC_E_WRONG_TRIGG_SRC);
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check Group is called in valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the SpinLock */
    ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if (Adc_UnLockedStatus(Adc_StopGroupConversionInfo[Group].blBufferLock))                                            /* PRQA S 2844, 3432 # JV-01, JV-01 */
    {
      Adc_LockProcess(Adc_StopGroupConversionInfo[Group].blBufferLock);                                                 /* PRQA S 2844, 3432 # JV-01, JV-01 */
      /* Release the SpinLock */
      ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Adc_StopGroupConversionInfo[Group].blSetRequest = ADC_TRUE;                                                       /* PRQA S 2844 # JV-01 */
      /* Release Lock */
      Adc_UnLockProcess(Adc_StopGroupConversionInfo[Group].blBufferLock);                                               /* PRQA S 2844, 3432 # JV-01, JV-01 */
    }
    else
    {
      /* Release Lock */
      ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION_SID, ADC_E_REQUEST_FALSE);
    }
    #else
    /* Stop the conversion */
    Adc_HwStopGroupConversion(Group);
    #endif
  }
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_ReadGroup
**
** Service ID           : 0x04
**
** Description          : This API shall read the group conversion result of
**                        the last completed conversion round of the
**                        requested ADC channel group and stores the channel
**                        values starting at the DataBufferPtr address.
**                        The group channel values are stored in the ascending
**                        channel number order.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : DataBufferPtr
**
** Return Parameter     : Std_ReturnType
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GpGroupRamData, Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GblDriverStatus,
**                        Adc_GucNoOfGroups, Adc_GucCoreIndex
**
** Functions invoked    : Det_ReportError, Adc_PollingReadGroup, Adc_StateTransition, ADC_DET_RUNTIME_ERROR,
**                        ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_005, ADC_DUD_ACT_005_CRT001, ADC_DUD_ACT_005_CRT002,
** Reference ID         : ADC_DUD_ACT_005_ERR001, ADC_DUD_ACT_005_ERR002, ADC_DUD_ACT_005_ERR003,
** Reference ID         : ADC_DUD_ACT_005_GBL001, ADC_DUD_ACT_005_ERR004, ADC_DUD_ACT_005_ERR005
***********************************************************************************************************************/
#if (ADC_READ_GROUP_API == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_ReadGroup(Adc_GroupType Group,                                                /* PRQA S 1503 # JV-01 */
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr)                                                    /* PRQA S 3432 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  volatile P2CONST(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) LpChannelBuffer;
  #if (ADC_ENABLE_STREAMING == STD_ON)
  uint32 LulNumOfSamples;
  #endif
  uint32 LulOffset;
  uint8 LucSgUnitIndex;
  Std_ReturnType LucReadStatus;
  uint32 LulLoopCount;
  uint32 LulAvailChannelCount;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;

  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  #endif /* (ADC_MULTI_CORE_SUPPORT == STD_ON) */
  
  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */

  /* Initialize the return value */
  LucReadStatus = E_NOT_OK;

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if invalid data buffer pointer, NULL_PTR passed */
  else if (NULL_PTR == DataBufferPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP_SID, ADC_E_PARAM_POINTER);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  #if (ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT)
  /* Check if the Scan Group is mapped for polling mode */
  else if (ADC_POLLING_MODE == Adc_GpSgUnitConfig[Adc_GpGroupConfig[Group].ucSgUnitIndex].enFunctionalityModeType)      /* PRQA S 2824 # JV-01 */
  {
    /* Check ScanGroup is called in valid core or not */
    if (Adc_GucCoreIndex != LucCoreID)                                                                                 /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET core not call on master */
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP_SID, ADC_E_INVALID_CORE);
      LblDetErrFlag = ADC_TRUE;
    }
  }
  #endif
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
  /* Check if the Scan Group is mapped for interrupt mode */
  else if (ADC_INTERRUPT_MODE == Adc_GpSgUnitConfig[Adc_GpGroupConfig[Group].ucSgUnitIndex].enFunctionalityModeType)
  {
    LucCoreID = ADC_ONE << LucCoreID;
    /* Check Group is called in valid core or not */
    if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                           /* PRQA S 0404, 3416 # JV-01, JV-01 */
    {
      /* Report Error to DET core not call on master */
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP_SID, ADC_E_INVALID_CORE);
      LblDetErrFlag = ADC_TRUE;
    }
  }
  #endif
  #endif /* (ADC_MULTI_CORE_SUPPORT == STD_ON) */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if the requested group is in state ADC_IDLE and there is no data to read */
    if ((ADC_IDLE == Adc_GpGroupRamData[Group].enGroupStatus) && (ADC_TRUE == Adc_GpGroupRamData[Group].blResultRead))  /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP_SID, ADC_E_IDLE);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */

    #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
    /* Check if the requested group has been pushed to the queue */
    if (ADC_TRUE == Adc_GpGroupRamData[Group].blGrpPresent)                                                             /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_READ_GROUP_SID, ADC_E_IDLE);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
    #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {  
    /* Get the pointer to requested group configuration */
    LpGroup = &Adc_GpGroupConfig[Group];                                                                                /* PRQA S 2824 # JV-01 */
    /* Get the SGx unit to which the channel group is mapped */
    LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                            /* PRQA S 2814 # JV-01 */

    /* Get the pointer to group ram data */
    LpGroupData = &Adc_GpGroupRamData[Group];                                                                           /* PRQA S 2824 # JV-01 */

    #if (ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT)
    /* Check if the Scan Group is mapped for polling mode */
    if (ADC_POLLING_MODE == Adc_GpSgUnitConfig[LucSgUnitIndex].enFunctionalityModeType)                                 /* PRQA S 2824 # JV-01 */
    {
      /* Call the internal read group function */
      Adc_PollingReadGroup(Group);
    } /* else: No action required */
    #endif /* (ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT) */

    if (ADC_BUSY != LpGroupData->enGroupStatus)                                                                         /* PRQA S 2814 # JV-01 */
    {
      #if (ADC_ENABLE_PWM_DIAG == STD_ON)
      if (ADC_TRUE == LpGroup->blPwmDiag)
      {
        /* Get the number of data for PWM-Diag as it is data and information. */
        LulAvailChannelCount = ADC_PWM_DIAG_NUM_DATA;
      }
      else
      #endif
      {
        /* Get the number of channels available for the requested group */
        LulAvailChannelCount = (uint32)LpGroupData->ucChannelCount;
      }
      /* Get the base address of the Group buffer */
      LpChannelBuffer = LpGroupData->pChannelBuffer;

      #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
      /* Check if the Scan Group is mapped for interrupt mode */
      if (ADC_INTERRUPT_MODE == Adc_GpSgUnitConfig[LucSgUnitIndex].enFunctionalityModeType)                             /* PRQA S 2824 # JV-01 */
      {
        /* Enter Global Protect area */
        ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      }
      else
      #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
      {
        /* Enter Protect area */
        ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);
      }
      #if (ADC_ENABLE_STREAMING == STD_ON)
      /* Get the number of samples configured for the group */
      LulNumOfSamples = (uint32)LpGroup->ddNumberofSamples;
      if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode)
      {
        /* Get the number of samples completed in the requested group */
        LulLoopCount = (uint32)LpGroupData->ucSamplesCompleted;
        /* Initialize the pointer to the latest sample of the first channel */
        LpChannelBuffer = &LpChannelBuffer[LulLoopCount - 1UL];                                                         /* PRQA S 2824, 2934, 3383 # JV-01, JV-01, JV-01 */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_STREAMING == STD_ON) */

      /* Initialize the loop count to zero */
      LulLoopCount = 0UL;
      do
      {
        #if (ADC_ENABLE_STREAMING == STD_ON)
        LulOffset = LulLoopCount * LulNumOfSamples;                                                                     /* PRQA S 3383 # JV-01 */
        #else
        LulOffset = LulLoopCount;
        #endif
        /* Load the converted values to the application buffer */
        DataBufferPtr[LulLoopCount] = LpChannelBuffer[LulOffset];                                                       /* PRQA S 2824, 2844 # JV-01, JV-01 */
        /* Increment to the next buffer index */
        LulLoopCount++;                                                                                                 /* PRQA S 3383 # JV-01 */
      } while (LulLoopCount < LulAvailChannelCount);

      #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
      /* Check if the Scan Group is mapped for interrupt mode */
      if (ADC_INTERRUPT_MODE == Adc_GpSgUnitConfig[LucSgUnitIndex].enFunctionalityModeType)                             /* PRQA S 2824 # JV-01 */
      {
        /* Change the group status of the group whose values are read */
        Adc_StateTransition(Group);
      } /* else: No action required */
      #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

      /* Set the flag indicating result data is read */
      LpGroupData->blResultRead = ADC_TRUE;
      #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
      /* Check if the Scan Group is mapped for interrupt mode */
      if (ADC_INTERRUPT_MODE == Adc_GpSgUnitConfig[LucSgUnitIndex].enFunctionalityModeType)                             /* PRQA S 2824 # JV-01 */
      {
        /* Exit Global Protect area */
        ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      }
      else
      #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
      {
        /* Exit Protect area */
        ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);
      }
      /* Update the return value */
      LucReadStatus = E_OK;
    } /* end of if (ADC_BUSY != LpGroupData->enGroupStatus) */
      /* else: No action required */
  } /* end of if (ADC_FALSE == LblDetErrFlag) */
    /* else: No action required */

  return LucReadStatus;
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_READ_GROUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_EnableHardwareTrigger
**
** Service ID           : 0x05
**
** Description          : This API service will enable the hardware trigger
**                        for the requested ADC Channel group.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GucMaxSwTriggGroups, Adc_GpGroupRamData,
**                        Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError, Adc_HwEnableHardwareTrigger, ADC_DET_RUNTIME_ERROR, Adc_UnLockedStatus
**                        Adc_UnLockProcess, Adc_LockProcess, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION  
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_006, ADC_DUD_ACT_006_ERR001, ADC_DUD_ACT_006_ERR002,
** Reference ID         : ADC_DUD_ACT_006_ERR003, ADC_DUD_ACT_006_ERR004, ADC_DUD_ACT_006_ERR005
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHardwareTrigger(Adc_GroupType Group)                                              /* PRQA S 1503 # JV-01 */
{
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;  
  
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */

  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check core is valid or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Check if requested group is SW triggered group */
    if (Group < Adc_GucMaxSwTriggGroups)
    {
      /* Report Error to DET */
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_WRONG_TRIGG_SRC);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
    #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */

    /* Check if the requested group is already enabled and not implicitly stopped */
    if ((ADC_TRUE == Adc_GpGroupRamData[Group].blHwTriggStatus) &&                                                      /* PRQA S 2824 # JV-01 */
        ((ADC_FALSE == Adc_GpGroupConfig[Group].blImplicitlyStopped) ||                                                 /* PRQA S 2824 # JV-01 */
         (ADC_STREAM_COMPLETED != Adc_GpGroupRamData[Group].enGroupStatus)))
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_BUSY);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */

    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Check if result buffer is initialized for requested group */
    if (ADC_FALSE == Adc_GpGroupRamData[Group].blBufferStatus)                                                          /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_BUFFER_UNINIT);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
    #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
    /* Enter global protect area */
    ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    /* Set request to master core if the shared buffer is ready - not locked by Satellite */
    if (Adc_UnLockedStatus(Adc_EnableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blBufferLock))                /* PRQA S 2844, 3383, 3432 # JV-01, JV-01, JV-01 */
    {
      Adc_LockProcess(Adc_EnableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blBufferLock);                     /* PRQA S 2844, 3383, 3432 # JV-01, JV-01, JV-01 */
      /* Exit global protect area */
      ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      /* Update the request */
      Adc_EnableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blSetRequest = ADC_TRUE;                           /* PRQA S 2844, 3383 # JV-01, JV-01 */
      /* Release Lock */
      Adc_UnLockProcess(Adc_EnableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blBufferLock);                   /* PRQA S 2844, 3383, 3432 # JV-01, JV-01, JV-01 */
    }
    else
    {
      /* Exit global protect area */
      ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      /* Report to Development Errors */
      (void)ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_REQUEST_FALSE);
    }
    #else
    /* Enable the hardware trigger */
    (void)Adc_HwEnableHardwareTrigger(Group);
    #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  } /* else: No action required */
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_DisableHardwareTrigger
**
** Service ID           : 0x06
**
** Description          : This API service will disables the hardware trigger
**                        for the requested ADC Channel group.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GucMaxSwTriggGroups, Adc_GpGroupRamData
**
** Functions invoked    : Det_ReportError, Adc_HwDisableHardwareTrigger, ADC_DET_RUNTIME_ERROR, Adc_UnLockedStatus,
**                        Adc_LockProcess, Adc_UnLockProcess, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_007, ADC_DUD_ACT_007_ERR001, ADC_DUD_ACT_007_ERR002,
** Reference ID         : ADC_DUD_ACT_007_ERR003, ADC_DUD_ACT_007_ERR004
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHardwareTrigger(Adc_GroupType Group)                                             /* PRQA S 1503 # JV-01 */
{
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */

  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if requested group is SW triggered group */
  else if (Group < Adc_GucMaxSwTriggGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER_SID, ADC_E_WRONG_TRIGG_SRC);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check core is valid or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if HW trigger was not enabled for requested group */
    if (ADC_FALSE == Adc_GpGroupRamData[Group].blHwTriggStatus)                                                         /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER_SID, ADC_E_IDLE);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    /* Check if HW trigger was enabled for requested group */
    if (ADC_TRUE == Adc_GpGroupRamData[Group].blHwTriggStatus)                                                          /* PRQA S 2824 # JV-01 */
    {
      #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
      /* Enter global protect area */
      ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      /* Set request to master core if the shared buffer is ready - not locked by Satellite */
      if (Adc_UnLockedStatus(Adc_DisableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blBufferLock))             /* PRQA S 2844, 3383, 3432 # JV-01, JV-01, JV-01 */
      {
        Adc_LockProcess(Adc_DisableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blBufferLock);                  /* PRQA S 2844, 3383, 3432 # JV-01, JV-01, JV-01 */
        /* Exit global protect area */
        ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        /* Update the request */
        Adc_DisableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blSetRequest = ADC_TRUE;                        /* PRQA S 2844, 3383 # JV-01, JV-01 */
        /* Release Lock */
        Adc_UnLockProcess(Adc_DisableHardwareTriggerInfo[Group - Adc_GucMaxSwTriggGroups].blBufferLock);                /* PRQA S 2844, 3383, 3432 # JV-01, JV-01, JV-01 */
      }
      else
      {
        /* Exit global protect area */
        ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        /* Report to Development Errors */
      (void)ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_HARDWARE_TRIGGER_SID,ADC_E_REQUEST_FALSE);
      }
      #else
      /* Disable the hardware trigger */
      Adc_HwDisableHardwareTrigger(Group);
      #endif
    } /* else: No action required */
  } /* else: No action required */
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_EnableGroupNotification
**
** Service ID           : 0x07
**
** Description          : This API service will enable the ADC Driver
**                        notification of the requested channel group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GpGroupConfig, Adc_GpGroupRamData
**
** Functions invoked    : Det_ReportError, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_008, ADC_DUD_ACT_008_ERR001, ADC_DUD_ACT_008_ERR002,
** Reference ID         : ADC_DUD_ACT_008_ERR003, ADC_DUD_ACT_008_GBL001
***********************************************************************************************************************/
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_EnableGroupNotification(Adc_GroupType Group)                                            /* PRQA S 1503 # JV-01 */
{
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION_SID, ADC_E_UNINIT);
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION_SID, ADC_E_PARAM_GROUP);
  }
  /* Check if no valid notification function is configured */
  else if (NULL_PTR == Adc_GpGroupConfig[Group].pGroupNotificationPointer)                                              /* PRQA S 2824 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION_SID, ADC_E_NOTIF_CAPABILITY);
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_GROUP_NOTIFICATION_SID, ADC_E_INVALID_CORE);
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Enter global Protect area */
    ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    /* Store the enabled notification into RAM */
    Adc_GpGroupRamData[Group].blNotifyStatus = ADC_TRUE;                                                                /* PRQA S 2824 # JV-01 */
    /* Exit global Protect area */
    ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
  }
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_DisableGroupNotification
**
** Service ID           : 0x08
**
** Description          : This API service will disable the ADC Driver
**                        notification of the requested channel group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GpGroupConfig, Adc_GpGroupRamData
**
** Functions invoked    : Det_ReportError, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION 
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_009, ADC_DUD_ACT_009_ERR001, ADC_DUD_ACT_009_ERR002,
** Reference ID         : ADC_DUD_ACT_009_ERR003, ADC_DUD_ACT_009_GBL001
***********************************************************************************************************************/
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_DisableGroupNotification(Adc_GroupType Group)                                           /* PRQA S 1503 # JV-01 */
{
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_GROUP_NOTIFICATION_SID, ADC_E_UNINIT);
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_GROUP_NOTIFICATION_SID, ADC_E_PARAM_GROUP);
  }
  /* Check if no valid notification function is configured */
  else if (NULL_PTR == Adc_GpGroupConfig[Group].pGroupNotificationPointer)                                              /* PRQA S 2824 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_GROUP_NOTIFICATION_SID, ADC_E_NOTIF_CAPABILITY);
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check Group is called with valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_GROUP_NOTIFICATION_SID, ADC_E_INVALID_CORE);
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Enter global Protect area */
    ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    /* Store the disabled notification into RAM */
    Adc_GpGroupRamData[Group].blNotifyStatus = ADC_FALSE;                                                               /* PRQA S 2824 # JV-01 */
    /* Exit global Protect area */
    ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
  }
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_GetGroupStatus
**
** Service ID           : 0x09
**
** Description          : This API service shall return the conversion status of
**                        requested ADC Channel group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : Adc_StatusType
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GucNoOfGroups, Adc_GpGroupRamData, Adc_GblDriverStatus, Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_010, ADC_DUD_ACT_010_ERR001, ADC_DUD_ACT_010_ERR002
***********************************************************************************************************************/
#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Adc_StatusType, ADC_PUBLIC_CODE) Adc_GetGroupStatus(Adc_GroupType Group)                                           /* PRQA S 1503 # JV-01 */
{
  /* Local variable to store the group status */
  Adc_StatusType LenGroupStatus;

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;

  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  
  /* Default value that to be returned in case of error */
  LenGroupStatus = ADC_IDLE;

  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;
  
  /* Check if the ADC Module is not Initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_GROUP_STATUS_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_GROUP_STATUS_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check group is called with valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_GROUP_STATUS_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  {
    /* No action required as group Id is valid */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the group status */
    LenGroupStatus = Adc_GpGroupRamData[Group].enGroupStatus;                                                           /* PRQA S 2824 # JV-01 */
  } /* else: No action required */

  return LenGroupStatus;
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_GetVersionInfo
**
** Service ID           : 0x0A
**
** Description          : This API service shall return the version information
**                        of ADC module.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : versioninfo
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : None
**
** Functions invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_011, ADC_DUD_ACT_011_ERR001
***********************************************************************************************************************/
#if (ADC_VERSION_INFO_API == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ADC_APPL_DATA)versioninfo)         /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_VERSION_INFO_SID, ADC_E_PARAM_POINTER);
  }
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    (versioninfo)->vendorID = (uint16)ADC_VENDOR_ID;                                                                    /* PRQA S 2814 # JV-01 */
    (versioninfo)->moduleID = (uint16)ADC_MODULE_ID;
    (versioninfo)->sw_major_version = (uint8)ADC_SW_MAJOR_VERSION;
    (versioninfo)->sw_minor_version = (uint8)ADC_SW_MINOR_VERSION;
    (versioninfo)->sw_patch_version = (uint8)ADC_SW_PATCH_VERSION;
  }
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_GetStreamLastPointer
**
** Service ID           : 0x0B
**
** Description          : This API service shall return the pointer to the last
**                        converted value for the group configured in streaming
**                        access mode.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group
**
** InOut Parameters     : None
**
** Output Parameters    : PtrToSamplePtr
**
** Return Parameter     : Adc_StreamNumSampleType
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GpGroupRamData, Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError, Adc_StateTransition, ADC_DET_RUNTIME_ERROR, ADC_ENTER_CRITICAL_SECTION,
**                        ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_012, ADC_DUD_ACT_012_CRT001, ADC_DUD_ACT_012_CRT002,
** Reference ID         : ADC_DUD_ACT_012_ERR001, ADC_DUD_ACT_012_ERR002, ADC_DUD_ACT_012_ERR003,
** Reference ID         : ADC_DUD_ACT_012_GBL001
***********************************************************************************************************************/
#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Adc_StreamNumSampleType, ADC_PUBLIC_CODE) Adc_GetStreamLastPointer(Adc_GroupType Group,                            /* PRQA S 1503 # JV-01 */
  P2VAR(P2VAR(Adc_ValueGroupType, ADC_APPL_DATA, ADC_APPL_DATA), AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr)              /* PRQA S 3432 # JV-01 */
{
  Adc_StreamNumSampleType LddSampleCount;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */

  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  
  /* Default value to be returned in case of error */
  *PtrToSamplePtr = NULL_PTR;                                                                                           /* PRQA S 2814 # JV-01 */
  LddSampleCount = ADC_VAL_BYTE_INIT;

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_STREAM_LAST_POINTER_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_STREAM_LAST_POINTER_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check group is called with valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_STREAM_LAST_POINTER_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if the requested group is in state ADC_IDLE and there is no data to read */
    if ((ADC_IDLE == Adc_GpGroupRamData[Group].enGroupStatus) && (ADC_TRUE == Adc_GpGroupRamData[Group].blResultRead))  /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_GET_STREAM_LAST_POINTER_SID, ADC_E_IDLE);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    if (ADC_BUSY != Adc_GpGroupRamData[Group].enGroupStatus)                                                            /* PRQA S 2824 # JV-01 */
    {
      /* Enter global Protect area */
      ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
      /* Get the number of samples completed for the requested group */
      LddSampleCount = Adc_GpGroupRamData[Group].ucSamplesCompleted;                                                    /* PRQA S 2824 # JV-01 */
      /* Load the pointer of the last converted value */
      *PtrToSamplePtr = (Adc_ValueGroupType *)&Adc_GpGroupRamData[Group].pChannelBuffer[LddSampleCount - ADC_BYTE_ONE];
      /* Change the group status of the group whose values are read */
      Adc_StateTransition(Group);
      /* Set the flag indicating result data is read */
      Adc_GpGroupRamData[Group].blResultRead = ADC_TRUE;
      /* Exit global Protect area */
      ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    } /* end of if (ADC_BUSY != Adc_GpGroupRamData[Group].enGroupStatus) */
      /* else: No action required */
  } /* end of if (ADC_FALSE == LblDetErrFlag) */
    /* else: No action required */

  /* Return the number of samples */
  return LddSampleCount;
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_SetupResultBuffer
**
** Service ID           : 0x0C
**
** Description          : Initializes the group specific ADC result buffer
**                        pointer as configured to point to the DataBufferPtr.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group, DataBufferPtr
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : Std_ReturnType
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GpGroupRamData, Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError, ADC_DET_RUNTIME_ERROR, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_013, ADC_DUD_ACT_013_ERR001, ADC_DUD_ACT_013_ERR002,
** Reference ID         : ADC_DUD_ACT_013_ERR003, ADC_DUD_ACT_013_ERR004, ADC_DUD_ACT_013_GBL001,
** Reference ID         : ADC_DUD_ACT_013_GBL002
***********************************************************************************************************************/
#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_SetupResultBuffer(Adc_GroupType Group,                                        /* PRQA S 1503 # JV-01 */
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr)                                                    /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucSetupStatus;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */

  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* (ADC_MULTI_CORE_SUPPORT == STD_ON) */
  
  /* Initialize the return value to E_NOT_OK */
  LucSetupStatus = E_NOT_OK;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Check if the ADC Module is not initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SETUP_RESULT_BUFFER_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the pointer for data buffer is *invalid */
  else if (NULL_PTR == DataBufferPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SETUP_RESULT_BUFFER_SID, ADC_E_PARAM_POINTER);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  } /* else: No action required */
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SETUP_RESULT_BUFFER_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check group is called with valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SETUP_RESULT_BUFFER_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if the requested group is not in state ADC_IDLE */
    if (ADC_IDLE != Adc_GpGroupRamData[Group].enGroupStatus)                                                            /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_SETUP_RESULT_BUFFER_SID, ADC_E_BUSY);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    /* Enter global Protect area */
    ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    /* Initialize the group result buffer pointer with the address passed */
    Adc_GpGroupRamData[Group].pChannelBuffer = DataBufferPtr;
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Set the buffer initialization status */
    Adc_GpGroupRamData[Group].blBufferStatus = ADC_TRUE;
    #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
    
    /* Exit global Protect area */
    ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    /* Update the return value */
    LucSetupStatus = E_OK;
  } /* else: No action required */

  return LucSetupStatus;
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DisableChannel
**
** Service ID           : 0xA0
**
** Description          : Disable the specified channel from group at the run
**                        time.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group, ChannelId
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GpGroupRamData, Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError, Adc_IntDisableEnableChannel, ADC_DET_RUNTIME_ERROR
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_014, ADC_DUD_ACT_014_ERR001, ADC_DUD_ACT_014_ERR002,
** Reference ID         : ADC_DUD_ACT_014_ERR004, ADC_DUD_ACT_014_ERR005
***********************************************************************************************************************/
#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_DisableChannel(Adc_GroupType Group, Adc_ChannelType ChannelId)                          /* PRQA S 1503 # JV-01 */
{
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */

  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if the ADC Module is not Initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_CHANNEL_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_CHANNEL_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check group is called with valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_CHANNEL_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if the group is already enabled */
    if (ADC_IDLE != Adc_GpGroupRamData[Group].enGroupStatus)                                                            /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_CHANNEL_SID, ADC_E_BUSY);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */

    #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
    /* Check if the group is present in queue */
    if (ADC_TRUE == Adc_GpGroupRamData[Group].blGrpPresent)                                                             /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_CHANNEL_SID, ADC_E_BUSY);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
    #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    /* Set the channel to be disabled from conversion after start group conversion. */
    Adc_IntDisableEnableChannel(Group, ChannelId, ADC_FALSE);
  } /* else: No action required */
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_DISABLE_CHANNEL == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_EnableChannel
**
** Service ID           : 0xA1
**
** Description          : Enable the specified channel from group at the run
**                        time.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Group, ChannelId
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GblDriverStatus, Adc_GucNoOfGroups, Adc_GpGroupRamData, Adc_GpGroupConfig
**
** Functions invoked    : Det_ReportError, Adc_IntDisableEnableChannel, ADC_DET_RUNTIME_ERROR
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_015, ADC_DUD_ACT_015_ERR001, ADC_DUD_ACT_015_ERR002,
** Reference ID         : ADC_DUD_ACT_015_ERR003, ADC_DUD_ACT_015_ERR004
***********************************************************************************************************************/
#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)

#define ADC_START_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PUBLIC_CODE) Adc_EnableChannel(Adc_GroupType Group, Adc_ChannelType ChannelId)                           /* PRQA S 1503 # JV-01 */
{
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = ADC_ONE << GetCoreID();
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */

  /* Initialize the Det error flag to ADC_FALSE */
  LblDetErrFlag = ADC_FALSE;

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Check if the ADC Module is not Initialized */
  if (ADC_UNINITIALIZED == Adc_GblDriverStatus)                                                                         /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_CHANNEL_SID, ADC_E_UNINIT);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  /* Check if the requested group is invalid group ID */
  else if (Group >= Adc_GucNoOfGroups)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_CHANNEL_SID, ADC_E_PARAM_GROUP);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
  /* Check group is called with valid core or not */
  else if ((Adc_GpGroupConfig[Group].ucGroupCoreIndex & LucCoreID) != LucCoreID)                                        /* PRQA S 0404, 2824, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Report to Development Errors */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_CHANNEL_SID, ADC_E_INVALID_CORE);
    /* Set the error status flag to ADC_TRUE */
    LblDetErrFlag = ADC_TRUE;
  }
  #endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if the group is already enabled */
    if (ADC_IDLE != Adc_GpGroupRamData[Group].enGroupStatus)                                                            /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_CHANNEL_SID, ADC_E_BUSY);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */

    #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
    /* Check if the group is present in queue */
    if (ADC_TRUE == Adc_GpGroupRamData[Group].blGrpPresent)                                                             /* PRQA S 2824 # JV-01 */
    {
      /* Report Error to DET */
      ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_CHANNEL_SID, ADC_E_BUSY);
      /* Set the error status flag to ADC_TRUE */
      LblDetErrFlag = ADC_TRUE;
    } /* else: No action required */
    #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
  }

  /* Check if no errors were detected */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    /* Set the channel to be enabled for conversion after start group conversion. */
    Adc_IntDisableEnableChannel(Group, ChannelId, ADC_TRUE);
  } /* else: No action required */
}

#define ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_DISABLE_CHANNEL == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
