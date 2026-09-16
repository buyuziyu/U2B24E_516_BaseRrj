/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Ocu_GTM_PBTypes.h                                                                                   */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of OCU Driver                                                                         */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.0: 30/05/2025 : Initial Version.
 */
/**********************************************************************************************************************/
#ifndef OCU_GTM_PBTYPES_H
#define OCU_GTM_PBTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Macro definitions */
#include "Ocu_Cfg.h"
/* Included for data type unsigned integer declaration */
#include "rh850_Types.h"
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define OCU_GTM_PBTYPES_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_GTM_PBTYPES_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_GTM_PBTYPES_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION
/* Software module version information */
#define OCU_GTM_PBTYPES_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_GTM_PBTYPES_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
/***********************************************************************************************************************
**                                                Global Symbols                                                      **
***********************************************************************************************************************/
/* Related GTM macros */
/* Macro for setting the GTM TOM/ATOM control register */
#define OCU_TOM_ATOM_CTRL_CLKSRC_MASK               (uint32)0xFFFF8FFFUL
#define OCU_ATOM_CTRL_SL_MASK                       (uint32)0x00000800UL
#define OCU_ATOM_CTRL_ACB10_HIGH                    (uint32)0x00000010UL
#define OCU_ATOM_CTRL_ACB10_LOW                     (uint32)0x00000020UL
#define OCU_ATOM_CTRL_ACB10_TOGGLE                  (uint32)0x00000030UL

/* Macro to enable the CCU0/CCU1 interrupt */
#define OCU_TOM_ATOM_ISR_CCU1_ENABLE                (uint32)0x00000002UL
#define OCU_TOM_ATOM_ISR_CCU01_ENABLE               (uint32)0x00000003UL

/* Macro for setting TBU unit */
#define OCU_TBU_CHANNEL_NO_CONFIG                   (uint32)0xFFFFFFFFUL
#define OCU_TBU0_CHANNEL_ENABLE                     (uint32)0x00000002UL
#define OCU_TBU1_CHANNEL_ENABLE                     (uint32)0x00000008UL
#define OCU_TBU2_CHANNEL_ENABLE                     (uint32)0x00000020UL

/* Ocu calculation value */
#define OCU_SHIFT_16                                16U
#define OCU_SHIFT_8                                 8U

/* Macro for setting GTM ATOM/TOM global control register */
#define OCU_TOM_ATOM_CTRL_ENABLE                    (uint32)0x00000002UL
#define OCU_TOM_ATOM_CTRL_DISABLE                   (uint32)0x00000001UL

/* GTM Unit Type */
#define OCU_HWIP_GTM_ATOM                           (uint8)0x00U
#define OCU_HWIP_GTM_TOM                            (uint8)0x01U

/* Macro for setting the counter register */
#define OCU_DOUBLE_ZERO                             (uint32)0x00000000UL
#define OCU_ATOM_MAX_COUNTER_VALUE                  (uint32)0x00FFFFFFUL
#define OCU_TBU_MAX_COUNTER_VALUE                   (uint32)0x00FFFFFFUL
#define OCU_TOM_MAX_COUNTER_VALUE                   (uint32)0x0000FFFFUL

/* Ocu calculation TBU cyclic data */
#define OCU_TBU_DIVIDE_PART                         (uint32)0x00555555UL
#define OCU_TBU_SECOND_PART                         (uint32)0x00555555UL
#define OCU_TBU_THIRD_PART                          (uint32)0x00AAAAAAUL
/***********************************************************************************************************************
**                                       Structure for GTM Tom Cluster registers                                     **
***********************************************************************************************************************/
#if (STD_ON == OCU_GTM_TOM_USED)
typedef struct STag_Ocu_GTMTomClusterRegs
{
  /* TOMi TGC y global control register */
  volatile uint32 ulTGCGLBCTRL;
  /* TOMi TGC y action time base register */
  volatile uint32 ulTGCACTTB;
  /* TOMi TGC y force update control register */
  volatile uint32 ulTGCFUPDCTRL;
  /* TOMi TGC y internal trigger control register */
  volatile uint32 ulTGCINTTRIG;
  /* Padding */
  volatile uint32 aaReserved[12];
  /* TOMi TGC y enable/disable control register */
  volatile uint32 ulTGCENDISCTRL;
  /* TOMi TGC y enable/disable status register */
  volatile uint32 ulTGCENDISSTAT;
  /* TOMi TGC y output enable control register */
  volatile uint32 ulTGCOUTENCTRL;
  /* TOMi TGC y output enable status register */
  volatile uint32 ulTGCOUTENSTAT;
}Ocu_GTMTomClusterRegs;

/***********************************************************************************************************************
**                                   Structure for GTM Tom Channel Control registers                                  **
***********************************************************************************************************************/
typedef struct STag_Ocu_GTMTomChCntrlRegs
{
  /* TOMi channel x control register */
  volatile uint32 ulCHxCTRL;
  /* TOMi channel x CCU0 compare shadow register */
  volatile uint32 ulCHxSR0;
  /* TOMi channel x CCU1 compare shadow register */
  volatile uint32 ulCHxSR1;
  /* TOMi channel x CCU0 compare register */
  volatile uint32 ulCHxCM0;
  /* TOMi channel x CCU1 compare register */
  volatile uint32 ulCHxCM1;
  /* TOMi channel x CCU0 counter register */
  volatile uint32 ulCHxCN0;
  /* TOMi channel x status register */
  volatile uint32 ulCHxSTAT;
  /* TOMi channel x interrupt notification register */
  volatile uint32 ulCHxIRQNOTIFY;
  /* TOMi channel x interrupt enable register */
  volatile uint32 ulCHxIRQEN;
  /* TOMi channel x force interrupt register */
  volatile uint32 ulCHxIRQFORCINT;
  /* TOMi channel x interrupt mode register */
  volatile uint32 ulCHxIRQMODE;
  /* TOMi channel x control register */
  volatile uint32 ulCHxCTRL2;
  /* TOMi channel x control shadow register */
  volatile uint32 ulCHxCTRLSR;
}Ocu_GTMTomChCntrlRegs;
#endif

/***********************************************************************************************************************
**                                       Structure for GTM Atom Cluster registers                                     **
***********************************************************************************************************************/
#if (STD_ON == OCU_GTM_ATOM_USED)
typedef struct STag_Ocu_GTMAtomClusterRegs
{
  /* ATOMi AGC global control register Registers */
  volatile uint32 ulAGCGLBCTRL;
  /* ATOMi AGC enable/disable control register */
  volatile uint32 ulAGCENDISCTRL;
  /* ATOMi AGC enable/disable status register */
  volatile uint32 ulAGCENDISSTAT;
  /* ATOMi AGC action time base register */
  volatile uint32 ulAGCACTTB;
  /* ATOMi AGC output enable control register */
  volatile uint32 ulAGCOUTENCTRL;
  /* ATOMi AGC output enable status register */
  volatile uint32 ulAGCOUTENSTAT;
  /* ATOMi AGC force update control register */
  volatile uint32 ulAGCFUPDCTRL;
  /* ATOMi AGC internal trigger control register */
  volatile uint32 ulAGCINTTRIG;
}Ocu_GTMAtomClusterRegs;

/***********************************************************************************************************************
**                                  Structure for GTM Atom Channel Control registers                                  **
***********************************************************************************************************************/
typedef struct STag_Ocu_GTMAtomChCntrlRegs
{
  /* ATOMi channel x control register */
  volatile uint32 ulCHxCTRL;
  /* ATOMi channel x CCU0 compare shadow register */
  volatile uint32 ulCHxSR0;
  /* ATOMi channel x CCU1 compare shadow register */
  volatile uint32 ulCHxSR1;
  /* ATOMi channel x CCU0 compare register */
  volatile uint32 ulCHxCM0;
  /* ATOMi channel x CCU1 compare register */
  volatile uint32 ulCHxCM1;
  /* ATOMi channel x CCU0 counter register */
  volatile uint32 ulCHxCN0;
  /* ATOMi channel x status register */
  volatile uint32 ulCHxSTAT;
  /* ATOMi channel x interrupt notification register */
  volatile uint32 ulCHxIRQNOTIFY;
  /* ATOMi channel x interrupt enable register */
  volatile uint32 ulCHxIRQEN;
  /* ATOMi channel x software interrupt generation */
  volatile uint32 ulCHxIRQFORCINT;
  /* ATOMi channel x interrupt mode configuration register */
  volatile uint32 ulCHxIRQMODE;
  /* ATOMi channel x control register */
  volatile uint32 ulCHxCTRL2;
  /* ATOMi channel x control shadow register */
  volatile uint32 ulCHxCTRLSR;
}Ocu_GTMAtomChCntrlRegs;
#endif

/***********************************************************************************************************************
**                                        Structure for GTM TBU channel registers                                     **
***********************************************************************************************************************/
#if (STD_ON == OCU_GTM_TBU_ATOM_SOMB_USED)
typedef struct STag_Ocu_GTMTbuChannelRegs
{
  /* TBU global channel enable */
  volatile uint32 ulTBUCHEN;
  /* TBU channel 0 control */
  volatile uint32 ulTBU0CTRL;
  /* TBU channel 0 base */
  volatile uint32 ulTBU0BASE;
  /* TBU channel 1 control */
  volatile uint32 ulTBU1CTRL;
  /* TBU channel 1 base */
  volatile uint32 ulTBU1BASE;
  /* TBU channel 2 control */
  volatile uint32 ulTBU2CTRL;
  /* TBU channel 2 base */
  volatile uint32 ulTBU2BASE;
  /* TBU channel 3 control */
  volatile uint32 ulTBU3CTRL;
  /* TBU channel 3 base */
  volatile uint32 ulTBU3BASE;
  /* TBU channel 3 modulo value */
  volatile uint32 ulTBU3BASEMASK;
  /* TBU channel 3 base captured */
  volatile uint32 ulTBU3BASECAPTURE;
}Ocu_GTMTbuChannelRegs;
#endif

/***********************************************************************************************************************
**                                  Data Structure for GTM channel configured data                                    **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_GTM == STD_ON)
typedef struct STag_Ocu_GTMChannelConfigType
{
  /* Pointer to base address of GTM TOM/ATOM cluster control registers */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pGtmTomATomClusterRegs;
  /* Pointer to base address of GTM TOM/ATOM channel control registers */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pGtmTomATomChannelRegs;
  /* Pointer to GTM_IRQ_SELxy register address */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pGTM_IRQ_SELxy;
  /* Value of GTM_IRQ_SELxy */
  uint32 ulGTM_IRQ_SELxyEnableValue;
  /* Value of ulTOM/ATOMCHxCTRL */
  uint32 ulCTRLRegValue;
  /* Channel bit mask */
  uint8 usChannelBitValue;
  /* ucGtmUnitType */
  uint8 ucGtmUnitType;
  #if(STD_ON == OCU_GTM_TBU_ATOM_SOMB_USED)
  /* TBU channel ID */
  uint8 ucTbuChannelNo;
  /* TBU ram index */
  uint8 ucTbuRamIndex;
  #endif
} Ocu_GTMChannelConfigType;
#endif

/***********************************************************************************************************************
**                                   Structure for TBUn cyclic data configuration                                   **
***********************************************************************************************************************/
#if (STD_ON == OCU_GTM_TBU_ATOM_SOMB_USED)
typedef struct STag_Ocu_GtmTbuUnitConfigType                                                                            /* PRQA S 3630 # JV-01 */
{
  /* Register address of GTM0TBUCHENR */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pTBUCHENRegs;
  /* Register value of GTM0TBU0CTRL */
  uint32 ulTBU0CTRLValue;
  /* Register value of GTM0TBU0CTRL */
  uint32 ulTBU1CTRLValue;
  /* Register value of GTM0TBU0CTRL */
  uint32 ulTBU2CTRLValue;
} Ocu_GtmTbuUnitConfigType;

/* Data Structure for OCU required for TBU Cyclic Event Compare data */
typedef struct STag_Ocu_GaaCyclicRamDataType
{
  /* Indicate the first Cyclic Event Compare to be occurred */
  uint32 ulFirstCyclicValue;
  /* Indicate the second Cyclic Event Compare to be occurred */
  uint32 ulSecondCyclicValue;
  /* Indicate the third Cyclic Event Compare to be occurred */
  uint32 ulThirdCyclicValue;
  /* Indicate the actual threshold */
  uint32 ulThresholdValue;
} Ocu_GaaCyclicRamDataType;
#endif

#endif /* End of file */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
