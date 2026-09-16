/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_GTM_PBTypes.h                                                                                   */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros and structure datatypes for post build parameters of GPT Driver                          */
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
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : As part of ticket ARDAACL-54181:
 *                       1. Add TOMnCHmCTRL2 and TOMnCHmCTRLSR registers into Gpt_TOMnCHmUnitRegs structure
 *                       2. Remove ucTimerUnitIndex from Gpt_GTMUnitConfigType structure
 *  2.3.0  28/02/2025  : Change value of GPT_CLKSRCCLEARVALUE macros
 *                     : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Initial Version.
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
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef GPT_GTM_PBTYPES_H
#define GPT_GTM_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Include difinition of multi instance */

/* Included for GPT module specific definitions */
#include "Gpt_Cfg.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_GTM_PBTYPES_AR_RELEASE_MAJOR_VERSION  GPT_AR_RELEASE_MAJOR_VERSION
#define GPT_GTM_PBTYPES_AR_RELEASE_MINOR_VERSION  GPT_AR_RELEASE_MINOR_VERSION
#define GPT_GTM_PBTYPES_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION
/* File version information */
#define GPT_GTM_PBTYPES_SW_MAJOR_VERSION    GPT_SW_MAJOR_VERSION
#define GPT_GTM_PBTYPES_SW_MINOR_VERSION    GPT_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
/* The macro for Enable/Disable registers */
#define GPT_DISABLEGTMCHmIRQEN              0U
#define GPT_ENABLEGTMCHmIRQEN               1U
#define GPT_DISABLETOMnCHmSR                (uint32)0x0000FFFFUL
#define GPT_DISABLETOMnCHmCM                (uint32)0x0000FFFFUL
#define GPT_DISABLEATOMnCHmSR               (uint32)0x00FFFFFFUL
#define GPT_DISABLEATOMnCHmCM               (uint32)0x00FFFFFFUL
#define GPT_CLKSRCCLEARVALUE                (uint32)0xFFFF0FFFUL
#define GPT_ENABLETGCmENDISCTRL             (uint32)0x00002222UL
#define GPT_ENABLETOMnTGCmGLBCTRL           (uint32)0x11110000UL
#define GPT_GTM_INTERRUPT_MATCH_MASK        (uint32)0x00000001UL
#define GPT_CLEAR_INTERRUPT_GTM             (uint32)0x00000001UL

/* The macro for Reset registers */
#define GPT_RESET_GTM_COUNTER               (uint32)0x00000000UL
#define GPT_RESET_TOMnCHm                   (uint32)0x00000000UL
#define GPT_RESET_ATOMnCHm                  (uint32)0x00000000UL

/* The macro for select mode of registers */
#define GPT_TOM_PWM_MODE                    (uint32)0x00000000UL
#define GPT_ATOM_PWM_MODE                   (uint32)0x00000002UL
#define GPT_CHANNEL_INT_PULSE_MODE          (uint32)0x00000002UL
#define GPT_TOMATOM_ONE_SHOT                (uint32)0x04000000UL

/**********************************************************************************************************************
**                        Structure for TOMn TGCm unit register configuration                                        **
**********************************************************************************************************************/
#if ((GPT_TOM_UNIT_USED == STD_ON) || (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON))
typedef volatile struct STag_Gpt_TOMnTGCmUnitRegs
{
  volatile uint32 ulTOMnTGCmGLBCTRL;
  volatile uint32 ulReserved[15];
  volatile uint32 ulTOMnTGCmENDISCTRL;
  volatile uint32 ulTOMnTGCmENDISSTAT;
} Gpt_TOMnTGCmUnitRegs;
#endif

/***********************************************************************************************************************
**                        Structure for GTM Unit configuration type                                                   **
***********************************************************************************************************************/
typedef struct STag_Gpt_GTMUnitConfigType
{
  /* Pointer to base address of GTM Unit registers */
  void* pGtmTomAtomClusterRegs;
  /* The value for TOM[i]_TGC[g]_GLB_CTRL register */
  uint32 ucGtmTomATomClusterGlbCtrlRegVal;
  /* The value for TOM[i]_TGC[g]_ENDIS_CTRL register */
  uint16 ucGtmTomATomClusterEnDisCtrlRegVal;
  /* The value for TOM[i]_TGC[g]_ENDIS_STAT register*/
  uint16 ucGtmTomATomClusterEnDisStsRegVal;
  /* Specify GTM TOM or ATOM sub unit */
  uint8 ucTomAtomTypeChannel;
} Gpt_GTMUnitConfigType;

/***********************************************************************************************************************
**                        Structure for TOMn Channel m unit register configuration                                    **
***********************************************************************************************************************/
#if ((GPT_TOM_UNIT_USED == STD_ON) || (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON))
typedef volatile struct STag_Gpt_TOMnCHmUnitRegs                                                                        /* PRQA S 3630 # JV-01 */
{
  volatile uint32 ulTOMnCHmCTRL;
  volatile uint32 ulTOMnCHmSR0;
  volatile uint32 ulTOMnCHmSR1;
  volatile uint32 ulTOMnCHmCM0;
  volatile uint32 ulTOMnCHmCM1;
  volatile uint32 ulTOMnCHmCN0;
  volatile uint32 ulTOMnCHmSTAT;
  volatile uint32 ulTOMnCHmIRQNOTIFY;
  volatile uint32 ulTOMnCHmIRQEN;
  volatile uint32 ulReserved;
  volatile uint32 ulTOMnCHmIRQMODE;
  volatile uint32 ulTOMnCHmCTRL2;
  volatile uint32 ulTOMnCHmCTRLSR;
} Gpt_TOMnCHmUnitRegs;
#endif

/***********************************************************************************************************************
**                        Structure for ATOMn AGC unit register configuration                                         **
***********************************************************************************************************************/
#if ((GPT_ATOM_UNIT_USED == STD_ON) || (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON))
typedef volatile struct STag_Gpt_ATOMnAGCUnitRegs
{
  volatile uint32 ulATOMnAGCGLBCTRL;
  volatile uint32 ulATOMnAGCENDISCTRL;
  volatile uint32 ulATOMnAGCENDISSTAT;
} Gpt_ATOMnAGCUnitRegs;
#endif

/***********************************************************************************************************************
**                        Structure for ATOMn Channel m unit register configuration                                   **
***********************************************************************************************************************/
#if ((GPT_ATOM_UNIT_USED == STD_ON) || (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON))
typedef volatile struct STag_Gpt_ATOMnCHmUnitRegs                                                                       /* PRQA S 3630 # JV-01 */
{
  volatile uint32 ulATOMnCHmCTRL;
  volatile uint32 ulATOMnCHmSR0;
  volatile uint32 ulATOMnCHmSR1;
  volatile uint32 ulATOMnCHmCM0;
  volatile uint32 ulATOMnCHmCM1;
  volatile uint32 ulATOMnCHmCN0;
  volatile uint32 ulATOMnCHmSTAT;
  volatile uint32 ulATOMnCHmIRQNOTIFY;
  volatile uint32 ulATOMnCHmIRQEN;
  volatile uint32 ulReserved;
  volatile uint32 ulATOMnCHmIRQMODE;
  volatile uint32 ulATOMnCHmCTRL2;
  volatile uint32 ulATOMnCHmCTRLSR;
} Gpt_ATOMnCHmUnitRegs;
#endif

/***********************************************************************************************************************
**                                   Structure for channel information                                                **
***********************************************************************************************************************/
#if(GPT_TOM_UNIT_USED == STD_ON)
typedef struct STag_Gpt_TOMChannelConfigType
{
  /* pointer to TOM control register */
  Gpt_TOMnCHmUnitRegs* pTOMnCHmUnitRegs;
  /* value of clock select */
  uint32   ulClockselectValue;
  /* value of start channels value */
  uint32   ulCounterStartMaskValue;
  /* Pointer to GTM Interrupt select control register */
  volatile uint32* pGTM_IRQ_SELij;
   /* Enable GTM Interrupt select control register value */
  uint32 ulGTM_IRQ_SELijEnableValue;
} Gpt_TOMChannelConfigType;
#endif

#if(GPT_ATOM_UNIT_USED == STD_ON)
typedef struct STag_Gpt_ATOMChannelConfigType
{
  /* pointer to TOM control register */
  Gpt_ATOMnCHmUnitRegs* pATOMnCHmUnitRegs;
  /* value of clock select */
  uint32 ulClockselectValue;
  /* value of start channels value */
  uint32 ulCounterStartMaskValue;
  /* Pointer to GTM Interrupt select control register */
  volatile uint32* pGTM_IRQ_SELij;
   /* Enable GTM Interrupt select control register value */
  uint32 ulGTM_IRQ_SELijEnableValue;
} Gpt_ATOMChannelConfigType;
#endif

/***********************************************************************************************************************
**                                           Structure for GPT_PredefTimer                                            **
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
typedef struct STag_Gpt_PredefTimerGTMChannelConfigType
{
  uint8 ucTomAtomTypeChannel;
  volatile uint32* pPredefTimerCounterReg;
  volatile uint32* pPredefTimerChannelRegs;
  volatile uint32* pPredefTimermUnitRegs;
  uint32  ulPredefTimerClockselectValue;
  uint32  ulPredefTimerStartMaskValue;
  uint32  ucGtmTomATomClusterGlbCtrlRegVal;
} Gpt_PredefTimerGTMChannelConfigType;
#endif

/***********************************************************************************************************************
**                                 Global configuration constants                                                     **
***********************************************************************************************************************/
#define GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"

extern const Gpt_GTMUnitConfigType Gpt_GaaGTMUnitConfig[];                                                              /* PRQA S 3684 # JV-01 */

#define GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"

#endif  /* GPT_GTM_PBTYPES_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
