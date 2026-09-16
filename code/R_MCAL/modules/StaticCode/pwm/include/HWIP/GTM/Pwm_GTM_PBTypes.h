/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_GTM_PBTypes.h                                                                                   */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of PWM Driver                                                                         */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 * 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
 * 2.3.2: 29/04/2025 : As part of GTM support, following changes are made                                             **
 *                     1. Add macro PWM_GTM_VERSION, PWM_GTM_4_1_VERSION and PWM_GTM_4_1_VERSION to support GTM       **
 *                        version 3.5                                                                                 **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
 * 2.3.0: 28/02/2025 : To support QAC 11.6.0: Add message 3630                                                        **
 *                     Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

#ifndef PWM_GTM_PBTYPES_H
#define PWM_GTM_PBTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Macro definitions */
#include "Pwm.h"
/* Included for data type unsigned integer declaration */
#include "rh850_Types.h"
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_GTM_PBTYPES_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_GTM_PBTYPES_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_GTM_PBTYPES_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION
/* Software module version information */
#define PWM_GTM_PBTYPES_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_GTM_PBTYPES_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                Global Symbols                                                      **
***********************************************************************************************************************/
/* Define GTM version */
#define PWM_GTM_4_1_VERSION       0
#define PWM_GTM_3_5_VERSION       1

/* GTM MODE setting mask for ATOM/TOM[i]_CH[x]_CTRL bit1,0 MODE */
#define PWM_GTM_MODE_SOMP_VALUE       0x00000002UL

/* GTM Polarity setting mask for ATOM/TOM[i]_CH[x]_CTRL bit11 SL */
#define PWM_GTM_POLARITY_HIGH_VALUE   0x00000800UL

/* GTM CLK_SRC setting mask for ATOM/TOM[i]_CH[x]_CTRL bit14..12 CLK_SRC_SR */
#define PWM_GTM_CLKSRC_MASK           0xFFFF8FFFUL
#define PWM_GTM_CLKSRC_SHIFT_NUM      12

/* FREEZE setting mask for ATOM/TOM[i]_CH[x]_CTRL bit31 FREEZE */
#define PWM_GTM_CTRL_FREEZE_ONE             0x80000000UL

/* GTM Output Level status mask ATOM/TOM[i]_CH[x]_ISTAT bit0 */
#define PWM_GTM_STAT_OL_MASK                   0x00000001UL

#define PWM_GTM_DUTY_MATCH_MASK                0x00000001UL
#define PWM_GTM_CYCLE_MATCH_MASK               0x00000002UL
#define PWM_GTM_DUTY_CYCLE_MATCH_MASK          0x00000003UL

/* GTM (A)TOM[i]_T(A)GC[x]_GLB_CTRL UPENx_CTRL enable/disable value */
#define PWM_GTM_AGC_TGC_EN_VALUE               0x0000AAAAUL
#define PWM_GTM_AGC_TGC_DIS_VALUE              0x00005555UL
#define PWM_GTM_AGC_TGC_RST_VALUE              0x00000008UL

#define PWM_GTM_GLB_CTRL_HOST_TRIG_VALUE       0x00000001UL
#define PWM_GTM_SHIFT_16                       16

#define PWM_GTM_CTRL_ENABLE                    0x00000002UL
#define PWM_GTM_CTRL_DISABLE                   0x00000001UL
#define PWM_GTM_CTRL_CLEAR                     0x00000000UL

#define PWM_GTM_TOMTYPE                        0x00
#define PWM_GTM_ATOMTYPE                       0x01
#define PWM_DOUBLE_ZERO                        (uint32)0x00000000UL
#define PWM_ATOM_MAX_COUNTER_VALUE             (uint32)0x00FFFFFFUL
#define PWM_TOM_MAX_COUNTER_VALUE              (uint32)0x0000FFFFUL
#define PWM_GTM_CLK_SRC_MASK                   0x00007000UL

#define PWM_GTM_CLKSRC_CMUCLK0_VALUE   0x0
#define PWM_GTM_CLKSRC_CMUCLK1_VALUE   0x1
#define PWM_GTM_CLKSRC_CMUCLK2_VALUE   0x2
#define PWM_GTM_CLKSRC_CMUCLK3_VALUE   0x3
#define PWM_GTM_CLKSRC_CMUCLK4_VALUE   0x4
#define PWM_GTM_CLKSRC_CMUCLK5_VALUE   0x5
#define PWM_GTM_CLKSRC_CMUCLK6_VALUE   0x6
#define PWM_GTM_CLKSRC_CMUCLK7_VALUE   0x7
#define PWM_GTM_CLKSRC_CMUFCLK0_VALUE  0x0
#define PWM_GTM_CLKSRC_CMUFCLK1_VALUE  0x1
#define PWM_GTM_CLKSRC_CMUFCLK2_VALUE  0x2
#define PWM_GTM_CLKSRC_CMUFCLK3_VALUE  0x3
#define PWM_GTM_CLKSRC_CMUFCLK4_VALUE  0x4
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**           Structure for GTM Atom Cluster registers                         **
*******************************************************************************/
#if(STD_ON == PWM_GTM_TOM_USED)
typedef struct STag_Pwm_GTMTomClusterRegs
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
}Pwm_GTMTomClusterRegs;

/*******************************************************************************
**           Structure for GTM Tom Channel Control registers                 **
*******************************************************************************/

typedef struct STag_Pwm_GTMTomChCntrlRegs
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
  #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
  /* TOMi channel x control register */
  volatile uint32 ulCHxCTRL2;
  /* TOMi channel x control shadow register */
  volatile uint32 ulCHxCTRLSR;
  #endif
}Pwm_GTMTomChCntrlRegs;
#endif
/*******************************************************************************
**           Structure for GTM Atom Cluster registers                         **
*******************************************************************************/
#if(STD_ON == PWM_GTM_ATOM_USED)
typedef struct STag_Pwm_GTMAtomClusterRegs
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

}Pwm_GTMAtomClusterRegs;
/*******************************************************************************
**           Structure for GTM Atom Channel Control registers                 **
*******************************************************************************/
typedef struct STag_Pwm_GTMAtomChCntrlRegs
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
  #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
  /* ATOMi channel x control register */
  volatile uint32 ulCHxCTRL2;
  /* ATOMi channel x control shadow register */
  volatile uint32 ulCHxCTRLSR;
  #endif
}Pwm_GTMAtomChCntrlRegs;

#endif
/***********************************************************************************************************************
**                                  Data Structure for GTM Unit configuration type                                    **
***********************************************************************************************************************/
typedef struct STag_Pwm_GTMUnitConfigType                                                                               /* PRQA S 3630 # JV-01 */
{
  /* pointer to base address of GTM Unit user control registers */
  P2VAR(void, TYPEDEF, REGSPACE) pGtmTomATomClusterRegs;
  /* Mask enable value for all channels in a GTM */
  uint16 usEnableChannelValue;
  /* Mask for channel configured as synchronous enable */
  uint16 usSyncChannelMask;
  /* Specify GTM TOM or ATOM sub unit */
  uint8 ucTomAtomType;
} Pwm_GTMUnitConfigType;

/***********************************************************************************************************************
**                                  Data Structure for GTM channel configured data                                    **
***********************************************************************************************************************/
typedef struct STag_Pwm_GTMChannelPropType
{
  /* pointer to base address of GTM Unit user control registers */
  P2VAR(void, TYPEDEF, REGSPACE) pGtmTomATomChannelRegs;
  #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
  /* pointer to base address of selected EIC */
  P2VAR(volatile uint16, PWM_CONFIG_DATA, REGSPACE) pEICx_Address;
  /* pointer to GTM_IRQ_SELxy */
  P2VAR(volatile uint32, PWM_CONFIG_DATA, REGSPACE) pGTM_IRQ_SELxy;
  /* Value of GTM_IRQ_SELxy */
  uint32 ulGTM_IRQ_SELxyEnableValue;
  #endif
  /* indicate channel number */
  uint8 ucChClockSelect;
  /* Default period */
  Pwm_PeriodType ddDefault_Period;
  /* Default duty */
  Pwm_PeriodType ddDefault_Duty;
  /* Default period shift value */
  uint16 usPeriodShift;
  /* GTM TOM/ATOM timer index */
  uint8 ucTimerUnitIndex;
  /* GTM TOM/ATOM timer channel no */
  uint8 ucChannelNumber;
  /* Specify GTM TOM or ATOM sub unit */
  uint8 ucTomAtomType;
} Pwm_GTMChannelPropType;

/***********************************************************************************************************************
**                                  Data Structure for TOM/ATOM clock type                                            **
***********************************************************************************************************************/
#endif
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
