/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_PIC_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Internal functions implementation of ADC Driver Component                                                          */
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
 * 2.1.3: 31/10/2024 : As part of U2Ax support, following changes are made:
 *                     1.Updated QAC messages according to QAC analysis results.
 *                     2.Added macro ADC_IP_ADCK to cover LulCountPIC2ADTCFGk declaration
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.1.1: 12/07/2024 : As part of ARDAACL-36510 support, following changes are made:
 *                     1.Add local variable LulCountPIC2ADTCFGk to scan all triggers configured loop in function
 *                     Adc_PicInit
 * 2.0.1: 18/10/2023 : Support QAC Amendment 2, add message 3006
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 *        03/08/2023 : Add new QAC message PRQA (2:1006).
 * 1.4.5: 14/09/2022 : Updated QAC messages according to QAC analysis results.
 *        12/09/2022 : Fixed comments about 'No action required' and 'end of'.
 * 1.4.4: 31/08/2022 : Fixed typos in comments due to review findings.
 *        24/08/2022 : Updated information in function header comments.
 *        21/07/2022 : Updated PRQA comments based on the result of static analysis.
 *                     Updated Re-entrancy, Global Variables and Registers Used in function header comments.
 *        20/06/2022 : Applied re-design of U2Bx to U2Ax.
 * 1.4.3: 23/05/2022 : Updated QAC comments for U2Bx.
 *        18/05/2022 : Renamed ucSgUnitIndex in HW unit config to ucSgUnitOffset.
 *                     Added configuration existence check to functions Adc_PicInit() and Adc_PicDeInit() for U2Bx.
 *                     Fixed the typos in comments.
 *        15/04/2022 : Added internal function Adc_PicTriggInit for U2Bx.
 *                     Changed the HW trigger configuration to the new structures for U2Bx.
 * 1.4.1: 24/11/2021 : Changed the condition of compile switches to support ADCK.
 *                     Added initialization and de-initialization of PIC2 triggers.
 * 1.3.2: 09/09/2021 : Added synchronization after handling each bus group.
 *        06/09/2021 : Changed to Adc_Mapping.h from Adc_MemMap.h
 *        25/08/2021 : Filled in the blank fields in the function header comment.
 * 1.3.1: 07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        16/06/2021 : Added the required cast to a conditional expression.
 *                     Removed redundant initialization.
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        24/05/2021 : Removed unnecessary include headers.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 09/12/2020 : Update functions Adc_PicInit(), Adc_PicDeInit() to add
 *                     conditional compilation. Just compile the code block
 *                     setting for PIC2ADTCFGx registers in case
 *                     ADC_NUM_OF_CONVERT_TRIGGER_CONFIG_REG is not zero
 *        06/12/2020 : Add new function Adc_PicInit()
 *                     Remove the writing to PIC2ADTCFGx in functions
 *                     Adc_PicEnableHwTrigger() and Adc_PicDisableHwTrigger()
 *                     Update function Adc_PicDeInit() to reset
 *                     PIC2ADTCFGx register
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020 : Release
 * 1.0.1: 09/04/2020 : Add const qualifier for arguments of internal functions
 *                     that are never changed
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for version check macro definitions and type definitions */
#include "Adc.h"

/* Included for RAM variable declarations */
#include "Adc_Ram.h"
/* Included for the declaration of internal function prototypes */
#include "Adc_PIC_LLDriver.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ADC_PIC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_PIC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_PIC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_PIC_LLDRIVER_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_PIC_LLDRIVER_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_PIC_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ADC_PIC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc_PIC_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ADC_PIC_LLDRIVER_AR_RELEASE_MINOR_VERSION != ADC_PIC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc_PIC_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ADC_PIC_LLDRIVER_AR_RELEASE_REVISION_VERSION != ADC_PIC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc_PIC_LLDriver.c : Mismatch in Release Patch Version"
#endif

#if (ADC_PIC_LLDRIVER_SW_MAJOR_VERSION != ADC_PIC_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Adc_PIC_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ADC_PIC_LLDRIVER_SW_MINOR_VERSION != ADC_PIC_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Adc_PIC_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule  (Symbolic Name or Published        */
/*                       Macro's name), so this is accepted                                                           */
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
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

#if (ADC_ENABLE_PIC_TSEL == STD_ON)
#if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
/* Initialize Trigger Configuration Registers and Trigger Output Control Registers */
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PicTriggInit(void);
#endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
#endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

#if (ADC_ENABLE_PIC_TSEL == STD_ON)
/***********************************************************************************************************************
** Function Name        : Adc_PicInit
**
** Service ID           : NA
**
** Description          : This internal function performs initialization of the PIC unit register
**                        when there is one or more common trigger registers configured.
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
** Preconditions        : None
**
** Global Variables     : Adc_GpTriggOutConfigRegister, Adc_GpTriggOutConfigValue, Adc_GucMaxSwTriggGroups,
**                        Adc_GucNoOfGroups, Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwTriggConfig
**
** Functions invoked    : Adc_PicTriggInit
**
** Registers Used       : PIC20ADTEN4nj, PIC21ADTEN4nj, PIC21ADTEN4nj, PIC2ADTCFGk
**
** Reference ID         : ADC_DUD_ACT_074, ADC_DUD_ACT_074_REG001, ADC_DUD_ACT_074_REG002,
** Reference ID         : ADC_DUD_ACT_074_REG003, ADC_DUD_ACT_074_GBL001
***********************************************************************************************************************/
#if ((ADC_ENABLE_PIC_COMMON == STD_ON) || (ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_PicInit(void)                                                                          /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  #if (ADC_IP_ADCH == STD_ON)
  /* Pointer to the Trigger Output Configuration Register */
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpTriggOutConfigRegister;
  /* Declare local counter variable */
  uint32 LulLoopCount;
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if (ADC_IP_ADCK == STD_ON)
  P2VAR(volatile Adc_PicTriggConfigRegType, AUTOMATIC, REGSPACE) LpPicTriggConfigReg;
  P2CONST(uint32, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggConfigValue;
  #endif /* (ADC_IP_ADCK == STD_ON) */
  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Pointer to the configuration and registers */
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2CONST(Adc_PicTriggSelectRegGroupType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggSelectRegGroup;
  P2CONST(Adc_PicTriggSelectValueType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggSelectValue;
  P2VAR(volatile Adc_PicTriggSelectValueType, AUTOMATIC, ADC_VAR_NO_INIT) LpPicTriggSelectCurrent;
  P2VAR(volatile Adc_PicTriggSelectRegsType, AUTOMATIC, REGSPACE) LpPicTriggSelectRegs;
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  uint32 LulCount;
  #if (ADC_IP_ADCK == STD_ON)
  uint32 LulCountPIC2ADTCFGk;
  #endif /* (ADC_IP_ADCK == STD_ON) */
  uint32 LulUsed;
  Adc_GroupType LddGroup;
  uint8 LucSgUnitId;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  #if (ADC_IP_ADCH == STD_ON)
  /* Initialize all A/D Converter Trigger Output Configuration Registers with configured value */
  for (LulLoopCount = 0UL; LulLoopCount < (uint32)ADC_NUM_OF_CONVERT_TRIGGER_CONFIG_REG; LulLoopCount++)
  {
    /* Get the address of PIC2ADTCFGx registers */
    LpTriggOutConfigRegister = (P2VAR(volatile uint32, AUTOMATIC, REGSPACE))Adc_GpTriggOutConfigRegister[LulLoopCount]; 

    /* Write configuration value to A/D Converter Trigger Output Configuration Register */
    *LpTriggOutConfigRegister |= Adc_GpTriggOutConfigValue[LulLoopCount];
  }

  /* Perform synchronization for PIC2 */
  (void)*(P2VAR(volatile uint32, AUTOMATIC, REGSPACE))Adc_GpTriggOutConfigRegister[0];
  EXECUTE_SYNCP();
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Initialize Trigger Configuration Register and Trigger Output Control Registers */
  Adc_PicTriggInit();

  /* Check if configurations exist */
  if ((NULL_PTR != Adc_GpHwTriggConfig) &&
      (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggSelectReg) &&
      (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggSelectValue) &&
      (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggSelectCurrent))
  {
    /* Get the pointer to Trigger Output Selection Register Group, Configuration Value and Current Value */
    LpPicTriggSelectRegGroup = Adc_GpHwTriggConfig->pPicTriggSelectReg;
    LpPicTriggSelectValue = Adc_GpHwTriggConfig->pPicTriggSelectValue;
    LpPicTriggSelectCurrent = Adc_GpHwTriggConfig->pPicTriggSelectCurrent;

    /* Scan all HW triggered groups */
    for (LddGroup = Adc_GucMaxSwTriggGroups; LddGroup < Adc_GucNoOfGroups; LddGroup++)
    {
      /* Get the group configuration */
      LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                           /* PRQA S 2824 # JV-01 */

      /* Check if the Trigger Output Selection used */
      if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggSelectIndex)                                                            /* PRQA S 2814 # JV-01 */
      {
        /* Get the SG unit Id from SG unit configuration */
        LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                   /* PRQA S 2824 # JV-01 */
        LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                       /* PRQA S 2814 # JV-01 */

        /* Get the flags of the triggers used */
        LulUsed = (uint32)LpPicTriggSelectValue[LpGroup->ucPicTriggSelectIndex].ucPicTriggSelectUsed;

        /* Loop the number of Trigger Output Selection Register Groups */
        for (LulCount = 0UL; LulCount < ADC_NUM_OF_PIC_SELECT; LulCount++)
        {
          /* Check if the trigger is used */
          if (0UL != (LulUsed & (1UL << LulCount)))
          {
            /* Initialize the Trigger Output Selection Register */
            LpPicTriggSelectRegs = LpPicTriggSelectRegGroup->aaPicTriggSelectRegs[LulCount];
            LpPicTriggSelectRegs->aaPicTriggSelectReg[LucSgUnitId].usPIC2ADTENxnj = ADC_PIC2_TRG_SEL_INIT;              /* PRQA S 2814, 2844 # JV-01, JV-01 */

            /* Initialize the Trigger Output Selection Register Current Value */
            LpPicTriggSelectCurrent[LucSgUnitId].aaPicTriggSelectValue[LulCount] = ADC_PIC2_TRG_SEL_INIT;               /* PRQA S 2824 # JV-01 */
            LpPicTriggSelectCurrent[LucSgUnitId].ucPicTriggSelectUsed = ADC_PIC2_NOT_USED;
          } /* else: No action required */
        } /* end of for (LulCount = 0UL; LulCount < ADC_NUM_OF_PIC_SELECT; LulCount++) */
      } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggSelectIndex) */
        /* else: No action required */
    } /* end of for (LddGroup = Adc_GucMaxSwTriggGroups; LddGroup < Adc_GucNoOfGroups; LddGroup++) */
  } /*
     * end of if ((NULL_PTR != Adc_GpHwTriggConfig) &&
     *            (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggSelectReg) &&
     *            (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggSelectValue) &&
     *            (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggSelectCurrent))
     */
    /* else: No action required */
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  #if (ADC_IP_ADCK == STD_ON)
  /* Check if configurations exist */
  if ((NULL_PTR != Adc_GpHwTriggConfig) &&
      (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggConfigReg) &&
      (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggConfigValue))
  {
    /* Get the pointer to the Trigger Output Configuration Register and Value */
    LpPicTriggConfigReg = Adc_GpHwTriggConfig->pPicTriggConfigReg;
    LpPicTriggConfigValue = Adc_GpHwTriggConfig->pPicTriggConfigValue;

    /* Get the flags of the triggers used */
    LulUsed = Adc_GpHwTriggConfig->ulPicTriggConfigUsed;
    
    /* Init count value number of configured PIC2ADTCFGk register */
    LulCountPIC2ADTCFGk = 0UL;

    /* Scan all triggers configured */
    for (LulCount = 0UL; LulCount < ADC_NUM_OF_PIC_CONFIG; LulCount++)
    {
      /* Check if the trigger is used */
      if (0UL != (LulUsed & (1UL << LulCount)))
      {
        /* Initialize trigger configuration */
        LpPicTriggConfigReg->aaPIC2ADTCFGk[LulCount] = LpPicTriggConfigValue[LulCountPIC2ADTCFGk];                      /* PRQA S 2814, 2824 # JV-01, JV-01 */
        LulCountPIC2ADTCFGk++;                                                                                          /* PRQA S 3383 # JV-01 */
      } /* else: No action required */
    }
  } /*
     * end of if ((NULL_PTR != Adc_GpHwTriggConfig) &&
     *            (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggConfigReg) &&
     *            (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggConfigValue))
     */
    /* else: No action required */

  /* Perform synchronization for PIC2 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* (ADC_IP_ADCK == STD_ON) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* ((ADC_ENABLE_PIC_COMMON == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Adc_PicDeInit
**
** Service ID           : NA
**
** Description          : This internal function shall perform the de-initialization of the PIC unit registers.
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
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GpSgUnitConfig, Adc_GpTriggOutConfigRegister,
**                        Adc_GpTriggOutConfigValue, Adc_GpHwTriggConfig
**
** Functions invoked    : Adc_PicTriggInit
**
** Registers Used       : PIC2ADTEN5nj, PIC2ADTEN6nj, PIC2ADTEN7nj, PIC2ADTEN8nj, PIC2ADCHnEDGSEL, PIC2ADCHnTSELj,
**                        PIC2ADTCFGk
**
** Reference ID         : ADC_DUD_ACT_066, ADC_DUD_ACT_066_REG001, ADC_DUD_ACT_066_REG002,
** Reference ID         : ADC_DUD_ACT_066_REG003, ADC_DUD_ACT_066_REG004, ADC_DUD_ACT_066_REG005,
** Reference ID         : ADC_DUD_ACT_066_REG006, ADC_DUD_ACT_066_REG007, ADC_DUD_ACT_066_REG008,
** Reference ID         : ADC_DUD_ACT_066_REG009
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_PicDeInit(void)                                                                        /* PRQA S 1532 # JV-01 */
{
  #if (ADC_IP_ADCH == STD_ON)
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_PicRegisters, AUTOMATIC, REGSPACE) LpAdcPicRegisters;
  P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA) LpAdcPicTenRegisters;
  P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA) LpPIC2ADTENRegTbl;
  P2VAR(volatile Adc_Pic2ADTenType, AUTOMATIC, REGSPACE) LpPIC2ADTENReg;
  uint8 LucSgUnitId;
  uint8 LucSgLoopCount;
  uint8 LucNoOfHwSGUnit;
  uint8 LucLoopCount;
  uint8 LucTenCnt;
  uint32 LulDeInitPosition;
  Adc_Pic2ADTenType LddPicTenValue;
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if (ADC_IP_ADCK == STD_ON)
  P2VAR(volatile Adc_PicTriggConfigRegType, TYPEDEF, REGSPACE) LpPicTriggConfigReg;
  uint32 LulUsed;
  uint32 LulCount;
  #endif /* (ADC_IP_ADCK == STD_ON) */

  #if (ADC_ENABLE_PIC_COMMON == STD_ON)
  #if (ADC_IP_ADCH == STD_ON)
  P2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpTriggOutConfigRegister;
  uint8 LucPIC2ADTCFGxCount;
  #endif /* (ADC_IP_ADCH == STD_ON) */
  #endif /* (ADC_ENABLE_PIC_COMMON == STD_ON) */

  #if (ADC_IP_ADCH == STD_ON)
  LulDeInitPosition = ADC_VAL_DWORD_INIT;

  /* DE-INITIALIZATION OF EACH GROUP */
  for (LucLoopCount = ADC_VAL_BYTE_INIT; LucLoopCount < (uint8)ADC_MAX_HW_UNITS; LucLoopCount++)
  {
    /* Get the base configuration address of the hardware unit */
    LpAdcPicTenRegisters = (P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA))
      Adc_GpHwUnitConfig[LucLoopCount].pPicTenRegisters;

    /* Get the number of SG units configured for this HW unit */
    LucNoOfHwSGUnit = Adc_GpHwUnitConfig[LucLoopCount].ucSgUnitCount;

    for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucNoOfHwSGUnit; LucSgLoopCount++)
    {
      LpSgUnitConfig = &Adc_GpSgUnitConfig[LulDeInitPosition];
      /* Get the SG unit Id */
      LucSgUnitId = LpSgUnitConfig->ucSgUnitId;

      /* Check if the HW unit is having any PIC configuration */
      if (NULL_PTR != LpAdcPicTenRegisters)
      {
        for (LucTenCnt = ADC_VAL_BYTE_INIT; LucTenCnt < (uint8)ADC_NUM_OF_TEN_GROUP; LucTenCnt++)
        {
          /* Get the register address */
          LpPIC2ADTENRegTbl = &LpAdcPicTenRegisters[LucTenCnt];
          LpPIC2ADTENReg =
            (P2VAR(volatile Adc_Pic2ADTenType, AUTOMATIC, REGSPACE))LpPIC2ADTENRegTbl->ulPIC2ADTENnx[LucSgUnitId];

          /* Reset AD Converter Trigger Output Control Register when channel group is configure PIC */
          LddPicTenValue = *LpPIC2ADTENReg;
          if (ADC_PIC2_ADTEN_INIT != LddPicTenValue)
          {
            *LpPIC2ADTENReg = ADC_PIC2_ADTEN_INIT;
          } /* else: No action required */
        } /* end of for (LucTenCnt = ADC_VAL_BYTE_INIT; LucTenCnt < ADC_NUM_OF_TEN_GROUP; LucTenCnt++) */
      } /* end of if (NULL_PTR != LpAdcPicTenRegisters) */
        /* else: No action required */

      /* Get the base configuration address of the hardware unit */
      LpAdcPicRegisters = LpSgUnitConfig->pSgUnitPicBaseAddress;
      if (NULL_PTR != LpAdcPicRegisters)
      {
        /* Reset to default value when Scan group not de-init */
        if ((LpAdcPicRegisters->ulPIC2ADCnTSELx[LucSgUnitId] != ADC_PIC2_ADCX_EDGSEL_INIT) ||
            (LpAdcPicRegisters->usPIC2ADCnEDGSEL != ADC_PIC2_ADCX_EDGSEL_INIT))
        {
          LpAdcPicRegisters->ulPIC2ADCnTSELx[LucSgUnitId] = ADC_PIC2_ADCX_EDGSEL_INIT;
          LpAdcPicRegisters->usPIC2ADCnEDGSEL = ADC_PIC2_ADCX_EDGSEL_INIT;

          /* Dummy read for synchronization */
          (void)LpAdcPicRegisters->usPIC2ADCnEDGSEL;
        } /* else: No action required */
      } /* else: No action required */

      /* InitPosition is incrementation */
      LulDeInitPosition++;
    } /* end of for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucNoOfHwSGUnit; LucSgLoopCount++) */
  } /* end of for (LucLoopCount = ADC_VAL_BYTE_INIT; LucLoopCount < (uint8)ADC_MAX_HW_UNITS; LucLoopCount++) */
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if (ADC_ENABLE_PIC_COMMON == STD_ON)
  #if (ADC_IP_ADCH == STD_ON)
  /* Loop all A/D Converter Trigger Output Configuration Registers to reset */
  for (LucPIC2ADTCFGxCount = ADC_COUNT_BYTE_INIT; LucPIC2ADTCFGxCount < (uint8)ADC_NUM_OF_CONVERT_TRIGGER_CONFIG_REG;
       LucPIC2ADTCFGxCount++)
  {
    LpTriggOutConfigRegister =
      (P2VAR(volatile uint32, AUTOMATIC, REGSPACE))Adc_GpTriggOutConfigRegister[LucPIC2ADTCFGxCount];

    /* Write configuration value to A/D Converter Trigger Output Configuration Register */
    /* Reset the configuration value of A/D Converter Trigger Output Configuration Register */
    *LpTriggOutConfigRegister &= ~Adc_GpTriggOutConfigValue[LucPIC2ADTCFGxCount];
  }

  /* Dummy read for synchronization */
  (void)*(P2VAR(volatile uint32, AUTOMATIC, REGSPACE))Adc_GpTriggOutConfigRegister[0];
  /* Perform synchronization for PIC2 */
  EXECUTE_SYNCP();
  #endif /* (ADC_IP_ADCH == STD_ON) */
  #endif /* (ADC_ENABLE_PIC_COMMON == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Initialize Trigger Configuration Registers and Trigger Output Control Register */
  Adc_PicTriggInit();
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  #if (ADC_IP_ADCK == STD_ON)
  /* Check if configuration exists */
  if ((NULL_PTR != Adc_GpHwTriggConfig) && (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggConfigReg))
  {
    /* Get the pointer to the Trigger Output Configuration Register and Value */
    LpPicTriggConfigReg = Adc_GpHwTriggConfig->pPicTriggConfigReg;

    /* Get the flags of the triggers used */
    LulUsed = Adc_GpHwTriggConfig->ulPicTriggConfigUsed;

    /* Scan all triggers configured */
    for (LulCount = 0UL; LulCount < ADC_NUM_OF_PIC_CONFIG; LulCount++)
    {
      /* Check if the trigger is used */
      if (0UL != (LulUsed & (1UL << LulCount)))
      {
        /* Initialize trigger configuration */
        LpPicTriggConfigReg->aaPIC2ADTCFGk[LulCount] = ADC_PIC2_TRG_CFG_INIT;                                           /* PRQA S 2814 # JV-01 */
      } /* else: No action required */
    }
  } /* end of if ((NULL_PTR != Adc_GpHwTriggConfig) && (NULL_PTR != Adc_GpHwTriggConfig->pPicTriggConfigReg)) */
    /* else: No action required */
  #endif /* (ADC_IP_ADCK == STD_ON) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_PicTriggInit
**
** Service ID           : NA
**
** Description          : This internal function performs the initialization of the PIC unit registers associated with
**                        the ADC HW unit.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GpSgUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : PIC2ADCJnTSELj, PIC2ADCJnEDGSEL, PIC2ADTEN5nj, PIC2ADTEN6nj, PIC2ADTEN7nj, PIC2ADTEN8nj,
**                        PIC20ADCKnTSELj, PIC21ADCKnTSELj, PIC20ADCKnEDGSEL, PIC21ADCKnEDGSEL, PIC20ADTEN5nj,
**                        PIC20ADTEN7nj, PIC20ADTEN8nj, PIC21ADTEN5nj, PIC21ADTEN6nj, PIC21ADTEN7nj, PIC21ADTEN8nj
**
** Reference ID         : ADC_DUD_ACT_095, ADC_DUD_ACT_095_REG001, ADC_DUD_ACT_095_REG002, ADC_DUD_ACT_095_REG003
***********************************************************************************************************************/
#if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PicTriggInit(void)
{
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_PicTriggRegType, AUTOMATIC, REGSPACE) LpPicTriggReg;
  P2CONST(Adc_PicTriggControlRegsType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggControlRegs;
  P2VAR(volatile Adc_PicTriggControlRegType, AUTOMATIC, REGSPACE) LpPicTriggControlReg;
  uint32 LulHwUnitIndex;
  uint32 LulSgUnitIndex;
  uint32 LulSgUnitCount;
  uint32 LulCount;

  /* Scan all HW units configured */
  for (LulHwUnitIndex = 0UL; LulHwUnitIndex < (uint32)ADC_MAX_HW_UNITS; LulHwUnitIndex++)                               /* PRQA S 2877 # JV-01 */
  {
    /* Get the HW unit configuration */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LulHwUnitIndex];                                                               /* PRQA S 2824 # JV-01 */

    /* Loop with the number of PIC2s that have a trigger configuration. (E.g., PIC20/PIC21) */
    for (LulCount = 0UL; LulCount < ADC_NUM_OF_TRIGG_SELECT; LulCount++)                                                /* PRQA S 2877 # JV-01 */
    {
      /* Get the pointer to Trigger Configuration Register */
      LpPicTriggReg = LpHwUnitConfig->aaPicTriggReg[LulCount];                                                          /* PRQA S 2814 # JV-01 */

      /* Check if the pointer is valid */
      if (NULL_PTR != LpPicTriggReg)
      {
        /* Get the first index of SG unit in this HW unit */
        LulSgUnitIndex = (uint32)LpHwUnitConfig->ucSgUnitOffset;

        /* Scan all SG units configured in this HW unit */
        for (LulSgUnitCount = (uint32)LpHwUnitConfig->ucSgUnitCount; LulSgUnitCount > 0UL; LulSgUnitCount--)
        {
          /* Get the SG unit configuration */
          LpSgUnitConfig = &Adc_GpSgUnitConfig[LulSgUnitIndex];                                                         /* PRQA S 2824 # JV-01 */

          /* Initialize Trigger Selection Control Register */
          LpPicTriggReg->aaPIC2ADCXnTSELj[LpSgUnitConfig->ucSgUnitId] = ADC_PIC2_ADCX_TSEL_INIT;                        /* PRQA S 2814, 2844 # JV-01, JV-01 */

          /* Increment the SG unit index */
          LulSgUnitIndex++;                                                                                             /* PRQA S 3383 # JV-01 */
        }

        /* Initialize Trigger Edge Selection Control Register */
        LpPicTriggReg->usPIC2ADCXnEDGSEL = ADC_PIC2_ADCX_EDGSEL_INIT;
      } /* end of if (NULL_PTR != LpPicTriggReg) */
        /* else: No action required */
    } /* end of for (LulCount = 0UL; LulCount < ADC_NUM_OF_TRIGG_SELECT; LulCount++) */

    /* Get the pointer to Trigger Output Control Register Group */
    LpPicTriggControlRegs = LpHwUnitConfig->pPicTriggControlRegs;

    /* Check if the pointer is valid */
    if (NULL_PTR != LpPicTriggControlRegs)
    {
      /* Get the first index of SG unit in this HW unit */
      LulSgUnitIndex = (uint32)LpHwUnitConfig->ucSgUnitOffset;

      /* Scan all SG units configured in this HW unit */
      for (LulSgUnitCount = (uint32)LpHwUnitConfig->ucSgUnitCount; LulSgUnitCount > 0UL; LulSgUnitCount--)
      {
        /* Get the SG unit configuration */
        LpSgUnitConfig = &Adc_GpSgUnitConfig[LulSgUnitIndex];
        /* Loop with the number of Trigger Output Control Register Groups */
        for (LulCount = 0; LulCount < ADC_NUM_OF_PIC_CONTROL; LulCount++)                                               /* PRQA S 2877 # JV-01 */
        {
          /* Initialize Trigger Output Control Register */
          LpPicTriggControlReg = LpPicTriggControlRegs->aaPicTriggControlRegs[LulCount];
          LpPicTriggControlReg->aaPIC2ADTENxnj[LpSgUnitConfig->ucSgUnitId] = ADC_PIC2_TRG_CTL_INIT;                     /* PRQA S 2814, 2844 # JV-01, JV-01 */
        }
        LulSgUnitIndex++;                                                                                               /* PRQA S 3383 # JV-01 */
      }
    } /* end of if (NULL_PTR != LpPicTriggControlRegs) */
      /* else: No action required */
  } /* end of for (LulHwUnitIndex = 0UL; LulHwUnitIndex < (uint32)ADC_MAX_HW_UNITS; LulHwUnitIndex++) */
}
#endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Adc_PicClearHwTrigger
**
** Service ID           : NA
**
** Description          : This function clear hardware trigger request for a Scan group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : PIC2ADCHnTSELj, PIC2ADCJnTSELj, PIC20ADCKnTSELj, PIC21ADCKnTSELj
**
** Reference ID         : ADC_DUD_ACT_067, ADC_DUD_ACT_067_REG001, ADC_DUD_ACT_067_REG002
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_PicClearHwTrigger(const Adc_GroupType LddGroup)                                        /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  uint8 LucSgUnitId;

  #if (ADC_IP_ADCH == STD_ON)
  P2VAR(volatile Adc_PicRegisters, AUTOMATIC, REGSPACE) LpAdcPicRegisters;
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_PicTriggRegType, AUTOMATIC, REGSPACE) LpPicTriggReg;
  uint32 LulCount;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  /* Read the hardware unit of the group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the SG unit Id */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */

  #if (ADC_IP_ADCH == STD_ON)
  /* Get the base configuration address of the hardware unit */
  LpAdcPicRegisters = LpSgUnitConfig->pSgUnitPicBaseAddress;

  /* Clear PIC2ADCnTSELx to avoid conversion on next HW trigger */
  LpAdcPicRegisters->ulPIC2ADCnTSELx[LucSgUnitId] = ADC_PIC2_ADCX_TSEL_INIT;
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Get the HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex];                                                         /* PRQA S 2824 # JV-01 */

  /* Check if the PIC Trigger used */
  if (ADC_HWTRIGG_OFF != LpGroup->ucTriggConfigIndex)
  {
    /* Loop with the number of PIC2s that have a trigger configuration. (E.g., PIC20/PIC21) */
    for (LulCount = 0UL; LulCount < ADC_NUM_OF_TRIGG_SELECT; LulCount++)                                                /* PRQA S 2877 # JV-01 */
    {
      /* Clear the Trigger Selection Register */
      LpPicTriggReg = LpHwUnitConfig->aaPicTriggReg[LulCount];                                                          /* PRQA S 2814 # JV-01 */
      LpPicTriggReg->aaPIC2ADCXnTSELj[LucSgUnitId] = ADC_PIC2_ADCX_TSEL_INIT;                                           /* PRQA S 2814, 2844 # JV-01, JV-01 */
    }
  } /* else: No action required */
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_PicEnableHwTrigger
**
** Service ID           : NA
**
** Description          : This internal function enables hardware trigger for a Scan group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant unless the request group uses the PIC2ADTEN4nj register
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GucMaxSwTriggGroups, Adc_GpHWGroupTrigg,
**                        Adc_GpHwUnitConfig, Adc_GpSGGroupTrigg, Adc_GpHwTriggConfig
**
** Functions invoked    : None
**
** Registers Used       : PIC2ADCHnTSELj, PIC2ADCHnEDGSEL, PIC2ADCJnTSELj, PIC2ADCJnEDGSEL, PIC2ADTEN4kj,
**                        PIC2ADTEN5nj, PIC2ADTEN6nj, PIC2ADTEN7nj, PIC2ADTEN8nj, PIC20ADCKnTSELj, PIC21ADCKnTSELj,
**                        PIC20ADCKnEDGSEL, PIC21ADCKnEDGSEL, PIC20ADTEN4nj, PIC20ADTEN5nj, PIC20ADTEN7nj,
**                        PIC20ADTEN8nj, PIC21ADTEN4nj, PIC21ADTEN5nj, PIC21ADTEN6nj, PIC21ADTEN7nj, PIC21ADTEN8nj
**
** Reference ID         : ADC_DUD_ACT_068, ADC_DUD_ACT_068_REG001, ADC_DUD_ACT_068_REG002,
** Reference ID         : ADC_DUD_ACT_068_REG003, ADC_DUD_ACT_068_REG004, ADC_DUD_ACT_068_REG005,
** Reference ID         : ADC_DUD_ACT_068_REG006
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_PicEnableHwTrigger(const Adc_GroupType LddGroup)                                       /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  uint8 LucSgUnitId;

  #if (ADC_IP_ADCH == STD_ON)
  P2VAR(volatile Adc_PicRegisters, AUTOMATIC, REGSPACE) LpAdcPicRegisters;
  P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA) LpAdcPicTenRegisters;
  P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA) LpPIC2ADTENRegTbl;
  P2CONST(Adc_PicConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpSGGroupTrigg;
  P2VAR(volatile Adc_Pic2ADTenType, AUTOMATIC, REGSPACE) LpPIC2ADTENReg;
  Adc_GroupType LddVirGroup;
  uint8 LucTenCnt;
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Pointer to the HW unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;

  /* Pointer to the Trigger Output Control Register Group */
  P2CONST(Adc_PicTriggControlRegsType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggControlRegs;
  /* Pointer to the Trigger Output Control Register */
  P2VAR(volatile Adc_PicTriggControlRegType, AUTOMATIC, REGSPACE) LpPicTriggControlReg;
  /* Pointer to the Trigger Output Control Register Value */
  P2CONST(Adc_PicTriggControlValueType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggControlValue;

  /* Pointer to the Trigger Output Selection Register Group */
  P2CONST(Adc_PicTriggSelectRegGroupType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggSelectRegGroup;
  /* Pointer to the Trigger Output Selection Register Group */
  P2VAR(volatile Adc_PicTriggSelectRegsType, AUTOMATIC, REGSPACE) LpPicTriggSelectRegs;
  /* Pointer to the Trigger Output Selection Register Value */
  P2CONST(Adc_PicTriggSelectValueType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggSelectValue;
  /* Pointer to the Trigger Output Selection Register Current Value */
  P2VAR(volatile Adc_PicTriggSelectValueType, AUTOMATIC, ADC_VAR_NO_INIT) LpPicTriggSelectCurrent;

  /* Pointer to the Trigger Configuration Register */
  P2VAR(volatile Adc_PicTriggRegType, AUTOMATIC, REGSPACE) LpPicTriggReg;
  /* Pointer to the Trigger Configuration Register Value */
  P2CONST(Adc_TriggConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpTriggConfig;

  /* Store the flags of the triggers used */
  uint32 LulUsed;
  /* Store the loop counter */
  uint32 LulCount;
  /* Store the setting value */
  uint16 LusValue;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the SG unit to which the group is configured */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */

  #if (ADC_IP_ADCH == STD_ON)
  /* Get the index to HW trigger details of requested group */
  LddVirGroup = LddGroup - Adc_GucMaxSwTriggGroups;
  /* Get the base configuration address of the hardware unit */
  LpAdcPicRegisters = LpSgUnitConfig->pSgUnitPicBaseAddress;

  /* Configure for HW trigger values configured */
  LpAdcPicRegisters->ulPIC2ADCnTSELx[LucSgUnitId] = Adc_GpHWGroupTrigg[LddVirGroup];
  LpAdcPicRegisters->usPIC2ADCnEDGSEL = LpGroup->usTriggerEdgeValue;

  /* Check if the SG unit is having any PIC configuration */
  if (ADC_HWTRIGG_OFF != LpGroup->ucPicSetOffset)
  {
    /* Get the base configuration address of the hardware unit */
    LpAdcPicTenRegisters = (P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA))
      Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex].pPicTenRegisters;
    LpSGGroupTrigg = &Adc_GpSGGroupTrigg[LpGroup->ucPicSetOffset];

    for (LucTenCnt = ADC_VAL_BYTE_INIT; LucTenCnt < (uint8)ADC_NUM_OF_TEN_GROUP; LucTenCnt++)
    {
      /* Get the register address */
      LpPIC2ADTENRegTbl = &LpAdcPicTenRegisters[LucTenCnt];
      LpPIC2ADTENReg =
        (P2VAR(volatile Adc_Pic2ADTenType, AUTOMATIC, REGSPACE))LpPIC2ADTENRegTbl->ulPIC2ADTENnx[LucSgUnitId];

      /* Write configuration value to AD Converter Trigger Output Control Register */
      *LpPIC2ADTENReg = LpSGGroupTrigg->ddPICADTENxMask[LucTenCnt];
    }
  } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucPicSetOffset) */
    /* else: No action required */

  /* Perform synchronization for PIC2 */
  (void)LpAdcPicRegisters->usPIC2ADCnEDGSEL;
  EXECUTE_SYNCP();
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Get the HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex];                                                         /* PRQA S 2824 # JV-01 */

  /* Check if the Trigger Output Control Register used */
  if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggControlIndex)
  {
    /* Get the pointer to Trigger Output Control Register Group and Value */
    LpPicTriggControlRegs = LpHwUnitConfig->pPicTriggControlRegs;                                                       /* PRQA S 2814 # JV-01 */
    LpPicTriggControlValue = &Adc_GpHwTriggConfig->pPicTriggControlValue[LpGroup->ucPicTriggControlIndex];              /* PRQA S 2814, 2824 # JV-01, JV-01 */

    /* Get the flags of the triggers used */
    LulUsed = (uint32)LpPicTriggControlValue->ucPicTriggControlUsed;                                                    /* PRQA S 2814 # JV-01 */

    /* Loop with the number of Trigger Output Control Register Groups */
    for (LulCount = 0; LulCount < ADC_NUM_OF_PIC_CONTROL; LulCount++)                                                   /* PRQA S 2877 # JV-01 */
    {
      /* Check if the trigger is used */
      if (0UL != (LulUsed & (1UL << LulCount)))
      {
        /* Set Trigger Output Control Register */
        LpPicTriggControlReg = LpPicTriggControlRegs->aaPicTriggControlRegs[LulCount];                                  /* PRQA S 2814 # JV-01 */
        LpPicTriggControlReg->aaPIC2ADTENxnj[LucSgUnitId] = LpPicTriggControlValue->aaPicTriggControlValue[LulCount];   /* PRQA S 2814, 2844 # JV-01, JV-01 */
      } /* else: No action required */
    }
  } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggControlIndex) */
    /* else: No action required */

  /* Check if the Trigger Selection Control Register used */
  if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggSelectIndex)
  {
    /* Get the pointers to Trigger Output Selection Register Group, Configuration Value and Current Value */
    /* These pointers are not null when the Trigger Selection Index has a valid value */
    LpPicTriggSelectRegGroup = Adc_GpHwTriggConfig->pPicTriggSelectReg;
    LpPicTriggSelectValue = &Adc_GpHwTriggConfig->pPicTriggSelectValue[LpGroup->ucPicTriggSelectIndex];                 /* PRQA S 2824 # JV-01 */
    LpPicTriggSelectCurrent = &Adc_GpHwTriggConfig->pPicTriggSelectCurrent[LucSgUnitId];                                /* PRQA S 2824 # JV-01 */

    /* Get the flags of the triggers used */
    LulUsed = (uint32)LpPicTriggSelectValue->ucPicTriggSelectUsed;                                                      /* PRQA S 2814 # JV-01 */

    /* Loop the number of Trigger Output Selection Register Groups */
    for (LulCount = 0UL; LulCount < ADC_NUM_OF_PIC_SELECT; LulCount++)
    {
      /* Check if the trigger is used */
      if (0UL != (LulUsed & (1UL << LulCount)))
      {
        /* Get the configuration value */
        LusValue = LpPicTriggSelectValue->aaPicTriggSelectValue[LulCount];

        /* Check if the set value is different from the current value */
        if (LpPicTriggSelectCurrent->aaPicTriggSelectValue[LulCount] != LusValue)                                       /* PRQA S 2814 # JV-01 */
        {
          /*Set the Trigger Output Selection Register */
          LpPicTriggSelectRegs = LpPicTriggSelectRegGroup->aaPicTriggSelectRegs[LulCount];                              /* PRQA S 2814 # JV-01 */
          LpPicTriggSelectRegs->aaPicTriggSelectReg[LucSgUnitId].usPIC2ADTENxnj = LusValue;                             /* PRQA S 2814, 2844 # JV-01, JV-01 */

          /* Store the set value as the current value */
          LpPicTriggSelectCurrent->aaPicTriggSelectValue[LulCount] = LusValue;
        } /* else: No action required */
      } /* end of if (0UL != (LulUsed & (1UL << LulCount))) */
        /* else: No action required */
    } /* end of for (LulCount = 0UL; LulCount < ADC_NUM_OF_PIC_SELECT; LulCount++) */
  } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggSelectIndex) */
    /* else: No action required */

  /* Check if the PIC Trigger used */
  if (ADC_HWTRIGG_OFF != LpGroup->ucTriggConfigIndex)
  {
    /* Get the pointer to Trigger Configuration Values */
    LpTriggConfig = &Adc_GpHwTriggConfig->pTriggConfig[LpGroup->ucTriggConfigIndex];                                    /* PRQA S 2824 # JV-01 */

    /* Loop with the number of PIC2s that have a trigger configuration. (E.g., PIC20/PIC21) */
    for (LulCount = 0UL; LulCount < ADC_NUM_OF_TRIGG_SELECT; LulCount++)
    {
      /* Get the Trigger Selection Control Register Value */
      LpPicTriggReg = LpHwUnitConfig->aaPicTriggReg[LulCount];

      /* Set Trigger Selection Control Register and Trigger Edge Selection Control Register */
      LpPicTriggReg->aaPIC2ADCXnTSELj[LucSgUnitId] = LpTriggConfig->aaTriggSelect[LulCount];                            /* PRQA S 2814, 2844 # JV-01, JV-01 */
      LpPicTriggReg->usPIC2ADCXnEDGSEL |= LpTriggConfig->usTriggEdge;

      /* When PIC2 trigger is used, this register is always set, so it is the only target for dummy reads */
      (void)LpPicTriggReg->usPIC2ADCXnEDGSEL;
      /* Perform synchronization for PIC2 */
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    } /* end of for (LulCount = 0UL; LulCount < ADC_NUM_OF_TRIGG_SELECT; LulCount++) */
  } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucTriggConfigIndex) */
    /* else: No action required */

  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_PicDisableHwTrigger
**
** Service ID           : NA
**
** Description          : This function disable hardware trigger for a Scan group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwUnitConfig, Adc_GpHwTriggConfig
**
** Functions invoked    : None
**
** Registers Used       : PIC2ADCHnTSELj, PIC2ADCHnEDGSEL, PIC2ADCJnTSELj, PIC2ADCJnEDGSEL, PIC2ADTEN5nj,
**                        PIC2ADTEN6nj, PIC2ADTEN7nj, PIC2ADTEN8nj, PIC20ADCKnTSELj, PIC21ADCKnTSELj,
**                        PIC20ADCKnEDGSEL, PIC21ADCKnEDGSEL, PIC20ADTEN5nj, PIC20ADTEN7nj, PIC20ADTEN8nj,
**                        PIC21ADTEN5nj, PIC21ADTEN6nj, PIC21ADTEN7nj, PIC21ADTEN8nj
**
** Reference ID         : ADC_DUD_ACT_069, ADC_DUD_ACT_069_REG001, ADC_DUD_ACT_069_REG002,
** Reference ID         : ADC_DUD_ACT_069_REG003, ADC_DUD_ACT_069_REG004, ADC_DUD_ACT_069_REG005
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_PicDisableHwTrigger(const Adc_GroupType LddGroup)                                      /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  uint8 LucSgUnitId;

  #if (ADC_IP_ADCH == STD_ON)
  P2VAR(volatile Adc_PicRegisters, AUTOMATIC, REGSPACE) LpAdcPicRegisters;
  P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA) LpAdcPicTenRegisters;
  P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA) LpPIC2ADTENRegTbl;
  P2VAR(volatile Adc_Pic2ADTenType, AUTOMATIC, REGSPACE) LpPIC2ADTENReg;
  uint8 LucTenCnt;
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Pointer to the HW unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;

  /* Pointer to the Trigger Output Control Register Group */
  P2CONST(Adc_PicTriggControlRegsType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggControlRegs;
  /* Pointer to the Trigger Output Control Register */
  P2VAR(volatile Adc_PicTriggControlRegType, AUTOMATIC, REGSPACE) LpPicTriggControlReg;
  /* Pointer to the Trigger Output Control Register Value */
  P2CONST(Adc_PicTriggControlValueType, AUTOMATIC, ADC_CONFIG_DATA) LpPicTriggControlValue;

  /* Pointer to the Trigger Configuration Register */
  P2VAR(volatile Adc_PicTriggRegType, AUTOMATIC, REGSPACE) LpPicTriggReg;
  /* Pointer to the Trigger Configuration Register Value */
  P2CONST(Adc_TriggConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpTriggConfig;

  /* Store the flags of the triggers used */
  uint32 LulUsed;
  /* Store the loop counter */
  uint32 LulCount;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the SG unit to which the group is configured */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */

  #if (ADC_IP_ADCH == STD_ON)
  /* Get the base configuration address of the hardware unit */
  LpAdcPicRegisters = LpSgUnitConfig->pSgUnitPicBaseAddress;

  /* Clear PIC2ADCXnTSELx to avoid conversion on next HW trigger */
  LpAdcPicRegisters->ulPIC2ADCnTSELx[LucSgUnitId] = ADC_PIC2_ADCX_TSEL_INIT;
  LpAdcPicRegisters->usPIC2ADCnEDGSEL = ADC_PIC2_ADCX_EDGSEL_INIT;

  /* Check if channel group is configure PIC using TAU */
  if (ADC_HWTRIGG_OFF != LpGroup->ucPicSetOffset)
  {
    /* Get the base configuration address of the hardware unit */
    LpAdcPicTenRegisters = (P2CONST(volatile Adc_PicTenRegisters, AUTOMATIC, ADC_CONFIG_DATA))
      Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex].pPicTenRegisters;

    for (LucTenCnt = ADC_VAL_BYTE_INIT; LucTenCnt < (uint8)ADC_NUM_OF_TEN_GROUP; LucTenCnt++)
    {
      /* Get the register address */
      LpPIC2ADTENRegTbl = &LpAdcPicTenRegisters[LucTenCnt];
      LpPIC2ADTENReg =
        (P2VAR(volatile Adc_Pic2ADTenType, AUTOMATIC, REGSPACE))LpPIC2ADTENRegTbl->ulPIC2ADTENnx[LucSgUnitId];

      /* Reset AD Converter Trigger Output Control Register */
      *LpPIC2ADTENReg = ADC_PIC2_ADTEN_INIT;
    }
  } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucPicSetOffset) */
    /* else: No action required */

  /* Perform synchronization for PIC2 */
  (void)LpAdcPicRegisters->usPIC2ADCnEDGSEL;
  EXECUTE_SYNCP();
  #endif /* (ADC_IP_ADCH == STD_ON) */

  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* Get the HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex];                                                         /* PRQA S 2824 # JV-01 */

  /* Check if the Trigger Output Control Register used */
  if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggControlIndex)
  {
    /* Get the pointer to Trigger Output Control Register Group and Value */
    LpPicTriggControlRegs = LpHwUnitConfig->pPicTriggControlRegs;                                                       /* PRQA S 2814 # JV-01 */
    LpPicTriggControlValue = &Adc_GpHwTriggConfig->pPicTriggControlValue[LpGroup->ucPicTriggControlIndex];              /* PRQA S 2814, 2824 # JV-01, JV-01 */

    /* Get the flags of the triggers used */
    LulUsed = (uint32)LpPicTriggControlValue->ucPicTriggControlUsed;                                                    /* PRQA S 2814 # JV-01 */

    /* Loop with the number of Trigger Output Control Register Groups */
    for (LulCount = 0; LulCount < ADC_NUM_OF_PIC_CONTROL; LulCount++)                                                   /* PRQA S 2877 # JV-01 */
    {
      /* Check if the trigger is used */
      if (0UL != (LulUsed & (1UL << LulCount)))
      {
        /* Initialize Trigger Output Control Register */
        LpPicTriggControlReg = LpPicTriggControlRegs->aaPicTriggControlRegs[LulCount];                                  /* PRQA S 2814 # JV-01 */
        LpPicTriggControlReg->aaPIC2ADTENxnj[LucSgUnitId] = ADC_PIC2_TRG_CTL_INIT;                                      /* PRQA S 2814, 2844 # JV-01, JV-01 */
      } /* else: No action required */
    }
  } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucPicTriggControlIndex) */
    /* else: No action required */

  /* Check if the PIC Trigger used */
  if (ADC_HWTRIGG_OFF != LpGroup->ucTriggConfigIndex)
  {
    /* Get the pointer to Trigger Configuration Values */
    LpTriggConfig = &Adc_GpHwTriggConfig->pTriggConfig[LpGroup->ucTriggConfigIndex];                                    /* PRQA S 2824 # JV-01 */

    /* Loop with the number of PIC2s that have a trigger configuration. (E.g., PIC20/PIC21) */
    for (LulCount = 0UL; LulCount < ADC_NUM_OF_TRIGG_SELECT; LulCount++)
    {
      /* Disable Trigger Selection Control Register and Trigger Edge Selection Control Register */
      LpPicTriggReg = LpHwUnitConfig->aaPicTriggReg[LulCount];
      LpPicTriggReg->aaPIC2ADCXnTSELj[LucSgUnitId] = ADC_PIC2_ADCX_TSEL_INIT;                                           /* PRQA S 2814, 2844 # JV-01, JV-01 */
      LpPicTriggReg->usPIC2ADCXnEDGSEL &= (uint16)~LpTriggConfig->usTriggEdge;                                          /* PRQA S 2814 # JV-01 */

      /* When PIC2 trigger is used, this register is always set, so it is the only target for dummy reads */
      (void)LpPicTriggReg->usPIC2ADCXnEDGSEL;
      /* Perform synchronization for PIC2 */
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    } /* end of for (LulCount = 0UL; LulCount < ADC_NUM_OF_TRIGG_SELECT; LulCount++) */
  } /* end of if (ADC_HWTRIGG_OFF != LpGroup->ucTriggConfigIndex) */
    /* else: No action required */
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
