/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Wdg_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Database declaration.                                                                                 */
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
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header 
 * 2.4.0:  30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E  
 *                         Add element WDTB6 into ETag_Wdg_WDTB_Unit_Number
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 *                         Remove message (1:1534), (1:1536) and update Copyright.
 * 2.0.1:  06/11/2023    : Correct register address offset of ECM register (ECMDTMCFG): update aaReserved7[33] to 
 *                         aaReserved7[672].
 *         21/10/2023    : Add Message (1:1534), (1:1536).
 * 2.0.0:  18/07/2023    : Delete #ifdef WDG_INSTANCE_INDEX macros related, delete Message (2:0841), 
 *                         add Message (2:1039), Message (2:3432), Message (2:3630), add structure Wdg_WDTB_Unit_Number,
 *                         Wdg_Error_ModeType, Wdg_WDTBAddress, Wdg_ECMAddress, Wdg_FEINTAddress, Wdg_ConfigUnit,
 *                         Wdg_UnitRegister, Wdg_GlobalAccessPointType, refined Wdg_ConfigType for supporting multicore
 * 1.4.3:  10/05/2022    : Update SW-VERSION
 *                         Remove marco WDG_DEM_NOT_USED
 * 1.4.1:  06/12/2021    : Add INST6 to support U2Bx devices
 * 1.3.1:  07/07/2021    : Add QAC message 9.5.0
 *                         Format source code to 120 characters
 *                         Improve Violation tag (remove START/END)
 *         30/06/2021    : 1) Change file name from Wdg_59_Types.h to Wdg_Types.h.
 *                         2) Update header file macro to call file multiple times.
 *                         3) Remove _VendorID ("_59") in all macros, struct name.
 * 1.2.0:  26/08/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.0:  25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1039)    : Treating array of length one as potentially flexible member.                                 */
/* Rule                : CERTCCM DCL38, MISRA C:2012 Dir-1.1, Rule-1.2                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef WDG_TYPES_HEADER
#define WDG_TYPES_HEADER

/***********************************************************************************************************************
**Include Section **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Structure declarations                                               **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define WDG_TYPES_AR_RELEASE_MAJOR_VERSION    WDG_AR_RELEASE_MAJOR_VERSION                                             
#define WDG_TYPES_AR_RELEASE_MINOR_VERSION    WDG_AR_RELEASE_MINOR_VERSION                                              
#define WDG_TYPES_AR_RELEASE_REVISION_VERSION WDG_AR_RELEASE_REVISION_VERSION                                           

/* Module Software version information */
#define WDG_TYPES_SW_MAJOR_VERSION            WDG_SW_MAJOR_VERSION                                                      
#define WDG_TYPES_SW_MINOR_VERSION            WDG_SW_MINOR_VERSION                                                      

/***********************************************************************************************************************
**                                                    Enumerators                                                     **
***********************************************************************************************************************/
#if (WDG_VAC_SUPPORT == STD_ON)
typedef enum ETag_Wdg_ActivationCode_ModeType                                                                            
{
  WDG_FIXED_ACTIVATION_CODE_MODE,
  WDG_VARIABLE_ACTIVATION_CODE_MODE
} Wdg_ActivationCode_ModeType;
#endif /* WDG_VAC_SUPPORT */

typedef enum ETag_Wdg_WDTB_Unit_Number                                                                                   
{
    WDG_WDTB0,
    WDG_WDTB1,
    WDG_WDTB2,
    WDG_WDTB3,
    WDG_WDTB4,
    WDG_WDTB5,
    WDG_WDTB6,
    WDG_WDTBA
} Wdg_WDTB_Unit_Number;

typedef enum ETag_Wdg_Error_ModeType                                                                                    
{
    WDG_RESET_MODE,
    WDG_FE_LEVEL_INTERRUPT_MODE
} Wdg_Error_ModeType;


/***********************************************************************************************************************
**                                               Structure declarations                                               **
***********************************************************************************************************************/
typedef struct ETag_Wdg_WDTBAddress                                                                                     /* PRQA S 3630 # JV-01 */
{
    uint8  volatile ucWdtbWDTE;      /* <WDTBn_base> + 0000H */
    uint8  volatile aaReserved[3];
    uint8  volatile ucWdtbEVAC;      /* <WDTBn_base> + 0004H */
    uint8  volatile aaReserved1[3];
    uint8  volatile ucWdtbREF;       /* <WDTBn_base> + 0008H */
    uint8  volatile aaReserved2[3];
    uint8  volatile ucWdtbMD;        /* <WDTBn_base> + 000CH */
    uint8  volatile aaReserved3[3];
    uint16 volatile usWdtbWOST;      /* <WDTBn_base> + 0010H */
    uint16 volatile usReserved4;
    uint16 volatile usWdtbWIS;       /* <WDTBn_base> + 0014H */
} Wdg_WDTBAddress;

typedef struct ETag_Wdg_ECMAddress                                                                                      /* PRQA S 3630 # JV-01 */
{
    uint32 volatile ulEcmISCFG;     /* <ECM_base> + j * 4H + 004H */
    uint8  volatile aaReserved5[536];
    uint32 volatile ulEcmIRCFG;     /* <ECM_base> + j * 4H + 220H */
    uint8  volatile aaReserved6[56];
    uint32 volatile ulEcmEMK;       /* <ECM_base> + j * 4H + 25CH */
    uint8 volatile aaReserved7[672];
    uint32 volatile ulEcmDTMCFG;    /* <ECM_base> + j * 4H + 500H */
} Wdg_ECMAddress;

typedef struct ETag_Wdg_FEINTAddress                                                                                    /* PRQA S 3630 # JV-01 */
{
    uint32 volatile ulFeintF;      /* <FEINC_PEx_base> */
    uint32 volatile ulFeintMsk;    /* <FEINC_PEx_base> +4H*/
    uint32 volatile ulFeintC;      /* <FEINC_PEx_base> +8H*/
} Wdg_FEINTAddress;

typedef struct STag_Wdg_ConfigUnit                                                                                      /* PRQA S 3630 # JV-01 */
{
  /* Option specifies the Window Open function mode */
  boolean blArbitraryTimingInterruptMode;
  /* Option selects delay timer start for error interrupt of FE level interrupt */
  boolean blEnableDelayTimerStart;
  /* Option select error signal output is masked or not */
  boolean blErrorOutputMask;
  /* Timing value of the WDTB interrupt generation timing */
  uint16 usInterruptOutputTimingSetting;
  /* Time starts value of the open-window period */
  uint16 usWindowOpenPeriodSetting;
  /* Configured Wdtb Unit Number */
  Wdg_WDTB_Unit_Number ddWdtbUnitNumber;
  /* Configured Error Mode */
  Wdg_Error_ModeType ddErrorModeSet;
  /* INTWDT Interrupt enable IMR mask */
  uint32 ulImrMask;
  /* Value of Ecmincfg E Int */
  uint32 ulEcmincfgEInt;
  /* Value to Enable Reset Mode */
  uint32 ulEnableResetMode;
  /* Value to Disable Reset Mode */
  uint32 ulDisableResetMode;
  /* Value of Timer Counter for Default mode */
  uint32 ulInitTimerCountValue;
  #if (WDG_DISABLE_ALLOWED == STD_ON)
  /* Value of 75% interrupt time for SLOW mode in micro-sec */
  uint32 ulSlowTimeValue;
  /* Value of 75% interrupt time for FAST mode in micro-sec */
  uint32 ulFastTimeValue;
  /* Value of interrupt time for arbitrary timing interrupt mode in micro-sec */
  uint32 ulSettingTimeValue;
  /* Value of WDTBMD register for SLOW mode */
  uint8 ucWdtbmdSlowValue;
  /* Value of WDTBMD register for FAST mode */
  uint8 ucWdtbmdFastValue;
  #else
  /* Watchdog disable is not allowed */
  /* Value of 75% interrupt time for Default mode in micro-sec */
  uint32 ulDefaultTimeValue;
  #endif /* End of (WDG_DISABLE_ALLOWED == STD_ON) */
  /* Value of WDTBMD register for Default mode */
  uint8 ucWdtbmdDefaultValue;
  /* Configured Default mode */
  WdgIf_ModeType ddWdtbmdDefaultMode;
  #if (WDG_VAC_SUPPORT == STD_ON)
  /* Variable Activation Code mode */
  Wdg_ActivationCode_ModeType ddActivationCodeMode;
  #endif /* WDG_VAC_SUPPORT */
} Wdg_ConfigUnit;

typedef struct STag_Wdg_UnitRegister                                                                                    /* PRQA S 3630 # JV-01 */
{
  /* WDTB registers */
  P2VAR( volatile Wdg_WDTBAddress, TYPEDEF, REGSPACE) pWDTBAddress;
  /* ECM registers */
  P2VAR( volatile Wdg_ECMAddress, TYPEDEF, REGSPACE) pECMAddress;
  /* FEINT Registers */
  P2VAR( volatile Wdg_FEINTAddress, TYPEDEF, REGSPACE) pFEINTAddress;
  /* ECM interrupt notification configuration register */
  volatile uint32* pEcmINCFG;
  /* ECM master error source status register */
  volatile uint32* pEcmMESSTR;
  /* EI Level Interrupt Mask Register */
  volatile uint32* pImr;
  /* EI level Interrupt Control Register */
  volatile uint16* pEic;
} Wdg_UnitRegister;

typedef struct STag_Wdg_ConfigType                                                                                     
{
  /* Database start value */
  uint32 ulStartOfDbToc;
  /* Array pointer to config Unit*/
  P2CONST(Wdg_ConfigUnit, TYPEDEF, WDG_APPL_CONST) aaUnitProperty[WDG_SUPPORTED_CORE_CONFIGURED_NUM];
  /* Array pointer to config register according to Unit*/
  P2CONST(Wdg_UnitRegister, TYPEDEF, REGSPACE) aaUnitRegister[WDG_SUPPORTED_CORE_CONFIGURED_NUM];                       /* PRQA S 1039 # JV-01 */
} Wdg_ConfigType;

#if (WDG_DEV_ERROR_DETECT == STD_ON)
/* Type definition for the current state of Watchdog Driver */
typedef enum ETag_Wdg_StatusType                                                                                        
{
  WDG_UNINIT,
  WDG_IDLE,
  WDG_BUSY
} Wdg_StatusType;
#endif

/* Global data for using across core */
typedef struct STag_Wdg_GlobalAccessPointType                                                                           
{
 #if (WDG_DEV_ERROR_DETECT == STD_ON)
  /* Driver Status for each core */
 volatile P2VAR(Wdg_StatusType, TYPEDEF, WDG_APPL_DATA) Wdg_GddDriverState;                                             /* PRQA S 3432 # JV-01 */
 #endif
  /* Global variable to store the current watchdog state */
 volatile P2VAR(WdgIf_ModeType, TYPEDEF, WDG_APPL_DATA) Wdg_GddCurrentMode;                                             /* PRQA S 3432 # JV-01 */
 /* Global variable to store the trigger counter value */
 volatile P2VAR(uint32, WDG_VAR_NO_INIT, WDG_APPL_DATA) Wdg_GulTriggerCounter;                                          /* PRQA S 3432 # JV-01 */
} Wdg_GlobalAccessPointType;

#endif /* WDG_TYPES_HEADER */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
