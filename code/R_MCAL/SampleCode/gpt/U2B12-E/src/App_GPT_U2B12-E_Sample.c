/*============================================================================*/
/* Project      = RH850/U2Bx,U2Cx MCAL Ver21.00.00.D                          */
/* Module       = App_GPT_U2B12-E_Sample.c                                    */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for GPT Driver Component             */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        U2B12-E                                       */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 *  2.3.1  31/03/2025  : Remove GPT_EIC_ADDR for TAUJ3
 *  2.3.0  28/02/2025  : As part of GTM HWIP support, following changes are made
 *                       Add EIC and setting clock for GTM
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 *  2.1.2  31/10/2024  : Update SW-VERSION for U2Bx Beta2 release
 *  2.0.3  29/04/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "App_GPT_Device_Sample.h"

/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/
#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)
#define GPT_EIC_BASE_ADDR       (0xFFF80000UL)
#define GPT_EIC_ADDR(n)         ((GPT_EIC_BASE_ADDR) + ((n) * 2UL))

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
uint32 RenICRADRR[] = {
              /* OSTMx (x6) */
              GPT_EIC_ADDR(360UL),
              GPT_EIC_ADDR(361UL),
              GPT_EIC_ADDR(841UL),
              GPT_EIC_ADDR(842UL),
              GPT_EIC_ADDR(968UL),
              GPT_EIC_ADDR(969UL),

              /* TAUJ2 (x4) */
              GPT_EIC_ADDR(960UL),
              GPT_EIC_ADDR(961UL),
              GPT_EIC_ADDR(962UL),
              GPT_EIC_ADDR(963UL),

              /* TAUD0 (x16) */
              0xFFFC0014UL,
              GPT_EIC_ADDR(320UL),
              0xFFFC0016UL,
              GPT_EIC_ADDR(321UL),
              0xFFFC0018UL,
              GPT_EIC_ADDR(322UL),
              0xFFFC001AUL,
              GPT_EIC_ADDR(323UL),
              0xFFFC002EUL,
              GPT_EIC_ADDR(324UL),
              0xFFFC0030UL,
              GPT_EIC_ADDR(325UL),
              0xFFFC0032UL,
              GPT_EIC_ADDR(326UL),
              0xFFFC0034UL,
              GPT_EIC_ADDR(327UL),

              /* TAUD1 (x16) */
              GPT_EIC_ADDR(328UL),
              GPT_EIC_ADDR(329UL),
              GPT_EIC_ADDR(330UL),
              GPT_EIC_ADDR(331UL),
              GPT_EIC_ADDR(332UL),
              GPT_EIC_ADDR(333UL),
              GPT_EIC_ADDR(334UL),
              GPT_EIC_ADDR(335UL),
              GPT_EIC_ADDR(336UL),
              GPT_EIC_ADDR(337UL),
              GPT_EIC_ADDR(338UL),
              GPT_EIC_ADDR(339UL),
              GPT_EIC_ADDR(340UL),
              GPT_EIC_ADDR(341UL),
              GPT_EIC_ADDR(342UL),
              GPT_EIC_ADDR(343UL),

              /* TAUD2 (x16) */
              GPT_EIC_ADDR(344UL),
              GPT_EIC_ADDR(345UL),
              GPT_EIC_ADDR(346UL),
              GPT_EIC_ADDR(347UL),
              GPT_EIC_ADDR(348UL),
              GPT_EIC_ADDR(349UL),
              GPT_EIC_ADDR(350UL),
              GPT_EIC_ADDR(351UL),
              GPT_EIC_ADDR(352UL),
              GPT_EIC_ADDR(353UL),
              GPT_EIC_ADDR(354UL),
              GPT_EIC_ADDR(355UL),
              GPT_EIC_ADDR(356UL),
              GPT_EIC_ADDR(357UL),
              GPT_EIC_ADDR(358UL),
              GPT_EIC_ADDR(359UL),

              /* TAUD3 (x16) */
              GPT_EIC_ADDR(379UL),
              GPT_EIC_ADDR(380UL),
              GPT_EIC_ADDR(381UL),
              GPT_EIC_ADDR(382UL),
              GPT_EIC_ADDR(383UL),
              GPT_EIC_ADDR(384UL),
              GPT_EIC_ADDR(385UL),
              GPT_EIC_ADDR(386UL),
              GPT_EIC_ADDR(387UL),
              GPT_EIC_ADDR(388UL),
              GPT_EIC_ADDR(389UL),
              GPT_EIC_ADDR(390UL),
              GPT_EIC_ADDR(391UL),
              GPT_EIC_ADDR(392UL),
              GPT_EIC_ADDR(393UL),
              GPT_EIC_ADDR(394UL),


              /* TAUD3 - Interrupt selection bit 100 */
              GPT_EIC_ADDR(793UL),
              GPT_EIC_ADDR(794UL),
              GPT_EIC_ADDR(795UL),
              GPT_EIC_ADDR(796UL),
              GPT_EIC_ADDR(797UL),
              GPT_EIC_ADDR(798UL),
              GPT_EIC_ADDR(799UL),
              GPT_EIC_ADDR(800UL),
              GPT_EIC_ADDR(801UL),
              GPT_EIC_ADDR(802UL),
              GPT_EIC_ADDR(803UL),
              GPT_EIC_ADDR(804UL),
              GPT_EIC_ADDR(817UL),
              GPT_EIC_ADDR(818UL),
              GPT_EIC_ADDR(819UL),
              GPT_EIC_ADDR(820UL),

              /* TAUD3 (x16) */
              GPT_EIC_ADDR(505UL),
              GPT_EIC_ADDR(506UL),
              GPT_EIC_ADDR(507UL),
              GPT_EIC_ADDR(508UL),
              GPT_EIC_ADDR(509UL),
              GPT_EIC_ADDR(510UL),
              GPT_EIC_ADDR(511UL),
              GPT_EIC_ADDR(512UL),
              GPT_EIC_ADDR(513UL),
              GPT_EIC_ADDR(514UL),
              GPT_EIC_ADDR(515UL),
              GPT_EIC_ADDR(516UL),
              GPT_EIC_ADDR(517UL),
              GPT_EIC_ADDR(518UL),
              GPT_EIC_ADDR(519UL),
              GPT_EIC_ADDR(520UL),

              /* TimerC000-C140 */
              GPT_EIC_ADDR(104UL),
              GPT_EIC_ADDR(108UL),
              GPT_EIC_ADDR(112UL),
              GPT_EIC_ADDR(116UL),
              GPT_EIC_ADDR(120UL),
              GPT_EIC_ADDR(124UL),
              GPT_EIC_ADDR(128UL),
              GPT_EIC_ADDR(132UL),
              GPT_EIC_ADDR(136UL),
              GPT_EIC_ADDR(140UL),
              GPT_EIC_ADDR(144UL),
              GPT_EIC_ADDR(148UL),
              GPT_EIC_ADDR(152UL),
              GPT_EIC_ADDR(156UL),
              GPT_EIC_ADDR(160UL),

              /* TimerD000-D110 */
              GPT_EIC_ADDR(164UL),
              GPT_EIC_ADDR(168UL),
              GPT_EIC_ADDR(172UL),
              GPT_EIC_ADDR(176UL),
              GPT_EIC_ADDR(180UL),
              GPT_EIC_ADDR(184UL),
              GPT_EIC_ADDR(188UL),
              GPT_EIC_ADDR(192UL),
              GPT_EIC_ADDR(196UL),
              GPT_EIC_ADDR(200UL),
              GPT_EIC_ADDR(204UL),
              GPT_EIC_ADDR(208UL),

              /* TimerG0-G13 */
              GPT_EIC_ADDR(272UL),
              GPT_EIC_ADDR(273UL),
              GPT_EIC_ADDR(274UL),
              GPT_EIC_ADDR(275UL),
              GPT_EIC_ADDR(276UL),
              GPT_EIC_ADDR(277UL),
              GPT_EIC_ADDR(278UL),
              GPT_EIC_ADDR(279UL),
              GPT_EIC_ADDR(280UL),
              GPT_EIC_ADDR(281UL),
              GPT_EIC_ADDR(282UL),
              GPT_EIC_ADDR(283UL),
              GPT_EIC_ADDR(284UL),
              GPT_EIC_ADDR(285UL),

              /* GTM */
              GPT_EIC_ADDR(86UL),
              GPT_EIC_ADDR(102UL),
                       };

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*    Setup peripheral guard to enable Read/write                             */
void Guard_Init(void)
{
    #if defined(RUN_OTHER_PE)
      INTC2_EIBD360 = 6;
      INTC2_EIBD361 = 6;
      INTC2_EIBD841 = 6;
      INTC2_EIBD963 = 6;
      INTC2_EIBD960 = 6;
      INTC2_EIBD961 = 6;
      INTC2_EIBD86  = 6;
      INTC2_EIBD102 = 6;
    #endif
    const uint32 RSLVX_base[]=
    {
        (uint32) 0xFFC6B000UL, //PBGERRSLV00_base
        (uint32) 0xFFC63100UL, //PBGERRSLV10_base
        (uint32) 0xFFDE1000UL, //PBGERRSLV20_base
        (uint32) 0xFFC73200UL, //PBGERRSLV30_base
        (uint32) 0xFFC75400UL, //PBGERRSLV40_base
        (uint32) 0xFFC7B000UL, //PBGERRSLV50_base
        (uint32) 0xFFC83000UL, //PBGERRSLV60_base
        (uint32) 0xFFC83040UL, //PBGERRSLV62_base
        (uint32) 0xFFF4A000UL, //PBGERRSLV70_base
        (uint32) 0xFFF2A000UL, //PBGERRSLV8H0_base
        (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
        (uint32) 0xFF0A1400UL, //PBGERRSLV90_base
        (uint32) 0xFF0A1500UL, //PBGERRSLV91_base
        (uint32) 0xFF87A000UL, //PBGERRSLV100_base
        (uint32) 0xFF8B2000UL, //PBGERRSLV11H0_base
        (uint32) 0xFF8F8100UL //PBGERRSLV11L0_base
    };
    const uint32 PBGXX_base[]=
    {
        (uint32) 0xFFC6B080UL, //PBG00_base
        (uint32) 0xFFC6B100UL, //PBG01_base
        (uint32) 0xFFC63000UL, //PBG10_base
        (uint32) 0xFF8B1600UL, //PBG11_base
        (uint32) 0xFFDE0B00UL, //PBG20_base
        (uint32) 0xFFDE0C00UL, //PBG21_base
        (uint32) 0xFFDE0D00UL, //PBG22_base
        (uint32) 0xFFDE0E00UL, //PBG23_base
        (uint32) 0xFFDE1200UL, //PBG24_base
        (uint32) 0xFFC72B00UL, //PBG30_base
        (uint32) 0xFFC72C00UL, //PBG31_base
        (uint32) 0xFFC72D00UL, //PBG32_base
        (uint32) 0xFFC75300UL, //PBG40_base
        (uint32) 0xFFC75380UL, //PBG41_base
        (uint32) 0xFFC7A300UL, //PBG50_base
        (uint32) 0xFFC7A400UL, //PBG51_base
        (uint32) 0xFFC7A500UL, //PBG52_base
        (uint32) 0xFFC81000UL, //PBG60_base
        (uint32) 0xFFC81200UL, //PBG61_base
        (uint32) 0xFFC82000UL, //PBG62_base
        (uint32) 0xFFF49400UL, //PBG70_base
        (uint32) 0xFFF49600UL, //PBG71_base
        (uint32) 0xFFF29300UL, //PBG8H0_base
        (uint32) 0xFF97A000UL, //PBG8L0_base
        (uint32) 0xFF0A1300UL, //PBG90_base
        (uint32) 0xFF0A1500UL, //PBG91_base
        (uint32) 0xFF0A1700UL, //PBG92_base
        (uint32) 0xFF879400UL, //PBG100_base
        (uint32) 0xFF879500UL, //PBG101_base
        (uint32) 0xFF8B1400UL, //PBG11H0_base
        (uint32) 0xFF8B1600UL, //PBG11H1_base
        (uint32) 0xFF8B1800UL, //PBG11H2_base
        (uint32) 0xFF8F8000UL, //PBG11L0_base
        (uint32) 0xFF860000UL, //PBG_CANFD0_base
        (uint32) 0xFF88FA00UL //PBG_ATU_base
    };

    for (int i =0; i<15;i++)
    {
        volatile uint32 *ptr;
        ptr = (volatile uint32 *)(RSLVX_base[i] + (uint32)0x18UL);
        *ptr = (uint32)0xA5A5A501UL;
    }

    //Write PBG0
    for (int i =0; i<34;i++)
    {
        for (int ii =0; ii<16;ii++)
        {
            volatile uint32 *ptr;
            ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
            *ptr |= 0x00000143UL;
        }
    }
    //Write PBG1
    for (int i =0; i<34;i++)
    {
        for (int ii =0; ii<16;ii++)
        {
            volatile uint32 *ptr;
            ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
            *ptr |= 0x07UL;
        }
    }
    //Disable write
    for (int i =0; i<15;i++)
    {
        volatile uint32 *ptr;
        ptr = (volatile uint32 *)(RSLVX_base[i]+0x18UL);
        *ptr = 0xA5A5A500UL;
    }
}
/* Function for Mcu clock settings */
void Mcu_Init(void)
{
  /* Initialize guard to un-protect for GPT HW units */
  Guard_Init();
#if 0
  /* Configure PBUS Guards register to permit access to INTC2 */
  FSGD0BPROT0 = 0x07FFFFFF;
#endif
  /* Mcu clock settings for the corresponding variant should be done here */

  /* Interrupt settings */
  /* Set Reference Table Method for TAUD0-3/TAUJ2-3/OSTM0-5/ATU6C/D/G */
    EIC10	|= (uint16)(1 << 6);
    EIC11	|= (uint16)(1 << 6);
    EIC12	|= (uint16)(1 << 6);
    EIC13	|= (uint16)(1 << 6);
    EIC23	|= (uint16)(1 << 6);
    EIC24	|= (uint16)(1 << 6);
    EIC25	|= (uint16)(1 << 6);
    EIC26	|= (uint16)(1 << 6);
    EIC104	|= (uint16)(1 << 6);
    EIC105	|= (uint16)(1 << 6);
    EIC106	|= (uint16)(1 << 6);
    EIC107	|= (uint16)(1 << 6);
    EIC108	|= (uint16)(1 << 6);
    EIC109	|= (uint16)(1 << 6);
    EIC110	|= (uint16)(1 << 6);
    EIC111	|= (uint16)(1 << 6);
    EIC112	|= (uint16)(1 << 6);
    EIC113	|= (uint16)(1 << 6);
    EIC114	|= (uint16)(1 << 6);
    EIC115	|= (uint16)(1 << 6);
    EIC116	|= (uint16)(1 << 6);
    EIC117	|= (uint16)(1 << 6);
    EIC118	|= (uint16)(1 << 6);
    EIC119	|= (uint16)(1 << 6);
    EIC120	|= (uint16)(1 << 6);
    EIC121	|= (uint16)(1 << 6);
    EIC122	|= (uint16)(1 << 6);
    EIC123	|= (uint16)(1 << 6);
    EIC124	|= (uint16)(1 << 6);
    EIC125	|= (uint16)(1 << 6);
    EIC126	|= (uint16)(1 << 6);
    EIC127	|= (uint16)(1 << 6);
    EIC128	|= (uint16)(1 << 6);
    EIC129	|= (uint16)(1 << 6);
    EIC130	|= (uint16)(1 << 6);
    EIC131	|= (uint16)(1 << 6);
    EIC132	|= (uint16)(1 << 6);
    EIC133	|= (uint16)(1 << 6);
    EIC134	|= (uint16)(1 << 6);
    EIC135	|= (uint16)(1 << 6);
    EIC136	|= (uint16)(1 << 6);
    EIC137	|= (uint16)(1 << 6);
    EIC138	|= (uint16)(1 << 6);
    EIC139	|= (uint16)(1 << 6);
    EIC140	|= (uint16)(1 << 6);
    EIC141	|= (uint16)(1 << 6);
    EIC142	|= (uint16)(1 << 6);
    EIC143	|= (uint16)(1 << 6);
    EIC144	|= (uint16)(1 << 6);
    EIC145	|= (uint16)(1 << 6);
    EIC146	|= (uint16)(1 << 6);
    EIC147	|= (uint16)(1 << 6);
    EIC148	|= (uint16)(1 << 6);
    EIC149	|= (uint16)(1 << 6);
    EIC150	|= (uint16)(1 << 6);
    EIC151	|= (uint16)(1 << 6);
    EIC152	|= (uint16)(1 << 6);
    EIC153	|= (uint16)(1 << 6);
    EIC154	|= (uint16)(1 << 6);
    EIC155	|= (uint16)(1 << 6);
    EIC156	|= (uint16)(1 << 6);
    EIC157	|= (uint16)(1 << 6);
    EIC158	|= (uint16)(1 << 6);
    EIC159	|= (uint16)(1 << 6);
    EIC160	|= (uint16)(1 << 6);
    EIC161	|= (uint16)(1 << 6);
    EIC162	|= (uint16)(1 << 6);
    EIC163	|= (uint16)(1 << 6);
    EIC164	|= (uint16)(1 << 6);
    EIC165	|= (uint16)(1 << 6);
    EIC166	|= (uint16)(1 << 6);
    EIC167	|= (uint16)(1 << 6);
    EIC168	|= (uint16)(1 << 6);
    EIC169	|= (uint16)(1 << 6);
    EIC170	|= (uint16)(1 << 6);
    EIC171	|= (uint16)(1 << 6);
    EIC172	|= (uint16)(1 << 6);
    EIC173	|= (uint16)(1 << 6);
    EIC174	|= (uint16)(1 << 6);
    EIC175	|= (uint16)(1 << 6);
    EIC176	|= (uint16)(1 << 6);
    EIC177	|= (uint16)(1 << 6);
    EIC178	|= (uint16)(1 << 6);
    EIC179	|= (uint16)(1 << 6);
    EIC180	|= (uint16)(1 << 6);
    EIC181	|= (uint16)(1 << 6);
    EIC182	|= (uint16)(1 << 6);
    EIC183	|= (uint16)(1 << 6);
    EIC184	|= (uint16)(1 << 6);
    EIC185	|= (uint16)(1 << 6);
    EIC186	|= (uint16)(1 << 6);
    EIC187	|= (uint16)(1 << 6);
    EIC188	|= (uint16)(1 << 6);
    EIC189	|= (uint16)(1 << 6);
    EIC190	|= (uint16)(1 << 6);
    EIC191	|= (uint16)(1 << 6);
    EIC192	|= (uint16)(1 << 6);
    EIC193	|= (uint16)(1 << 6);
    EIC194	|= (uint16)(1 << 6);
    EIC195	|= (uint16)(1 << 6);
    EIC196	|= (uint16)(1 << 6);
    EIC197	|= (uint16)(1 << 6);
    EIC198	|= (uint16)(1 << 6);
    EIC199	|= (uint16)(1 << 6);
    EIC200	|= (uint16)(1 << 6);
    EIC201	|= (uint16)(1 << 6);
    EIC202	|= (uint16)(1 << 6);
    EIC203	|= (uint16)(1 << 6);
    EIC204	|= (uint16)(1 << 6);
    EIC205	|= (uint16)(1 << 6);
    EIC206	|= (uint16)(1 << 6);
    EIC207	|= (uint16)(1 << 6);
    EIC208	|= (uint16)(1 << 6);
    EIC209	|= (uint16)(1 << 6);
    EIC210	|= (uint16)(1 << 6);
    EIC211	|= (uint16)(1 << 6);
    EIC272	|= (uint16)(1 << 6);
    EIC273	|= (uint16)(1 << 6);
    EIC274	|= (uint16)(1 << 6);
    EIC275	|= (uint16)(1 << 6);
    EIC276	|= (uint16)(1 << 6);
    EIC277	|= (uint16)(1 << 6);
    EIC278	|= (uint16)(1 << 6);
    EIC279	|= (uint16)(1 << 6);
    EIC280	|= (uint16)(1 << 6);
    EIC281	|= (uint16)(1 << 6);
    EIC282	|= (uint16)(1 << 6);
    EIC283	|= (uint16)(1 << 6);
    EIC284	|= (uint16)(1 << 6);
    EIC285	|= (uint16)(1 << 6);
    EIC320	|= (uint16)(1 << 6);
    EIC321	|= (uint16)(1 << 6);
    EIC322	|= (uint16)(1 << 6);
    EIC323	|= (uint16)(1 << 6);
    EIC324	|= (uint16)(1 << 6);
    EIC325	|= (uint16)(1 << 6);
    EIC326	|= (uint16)(1 << 6);
    EIC327	|= (uint16)(1 << 6);
    EIC328	|= (uint16)(1 << 6);
    EIC329	|= (uint16)(1 << 6);
    EIC330	|= (uint16)(1 << 6);
    EIC331	|= (uint16)(1 << 6);
    EIC332	|= (uint16)(1 << 6);
    EIC333	|= (uint16)(1 << 6);
    EIC334	|= (uint16)(1 << 6);
    EIC335	|= (uint16)(1 << 6);
    EIC336	|= (uint16)(1 << 6);
    EIC337	|= (uint16)(1 << 6);
    EIC338	|= (uint16)(1 << 6);
    EIC339	|= (uint16)(1 << 6);
    EIC340	|= (uint16)(1 << 6);
    EIC341	|= (uint16)(1 << 6);
    EIC342	|= (uint16)(1 << 6);
    EIC343	|= (uint16)(1 << 6);
    EIC344	|= (uint16)(1 << 6);
    EIC345	|= (uint16)(1 << 6);
    EIC346	|= (uint16)(1 << 6);
    EIC347	|= (uint16)(1 << 6);
    EIC348	|= (uint16)(1 << 6);
    EIC349	|= (uint16)(1 << 6);
    EIC350	|= (uint16)(1 << 6);
    EIC351	|= (uint16)(1 << 6);
    EIC352	|= (uint16)(1 << 6);
    EIC353	|= (uint16)(1 << 6);
    EIC354	|= (uint16)(1 << 6);
    EIC355	|= (uint16)(1 << 6);
    EIC356	|= (uint16)(1 << 6);
    EIC357	|= (uint16)(1 << 6);
    EIC358	|= (uint16)(1 << 6);
    EIC359	|= (uint16)(1 << 6);
    EIC360	|= (uint16)(1 << 6);
    EIC361	|= (uint16)(1 << 6);
    EIC379	|= (uint16)(1 << 6);
    EIC380	|= (uint16)(1 << 6);
    EIC381	|= (uint16)(1 << 6);
    EIC382	|= (uint16)(1 << 6);
    EIC383	|= (uint16)(1 << 6);
    EIC384	|= (uint16)(1 << 6);
    EIC385	|= (uint16)(1 << 6);
    EIC386	|= (uint16)(1 << 6);
    EIC387	|= (uint16)(1 << 6);
    EIC388	|= (uint16)(1 << 6);
    EIC389	|= (uint16)(1 << 6);
    EIC390	|= (uint16)(1 << 6);
    EIC391	|= (uint16)(1 << 6);
    EIC392	|= (uint16)(1 << 6);
    EIC393	|= (uint16)(1 << 6);
    EIC394	|= (uint16)(1 << 6);
    EIC505	|= (uint16)(1 << 6);
    EIC506	|= (uint16)(1 << 6);
    EIC507	|= (uint16)(1 << 6);
    EIC508	|= (uint16)(1 << 6);
    EIC509	|= (uint16)(1 << 6);
    EIC510	|= (uint16)(1 << 6);
    EIC511	|= (uint16)(1 << 6);
    EIC512	|= (uint16)(1 << 6);
    EIC513	|= (uint16)(1 << 6);
    EIC514	|= (uint16)(1 << 6);
    EIC515	|= (uint16)(1 << 6);
    EIC516	|= (uint16)(1 << 6);
    EIC517	|= (uint16)(1 << 6);
    EIC518	|= (uint16)(1 << 6);
    EIC519	|= (uint16)(1 << 6);
    EIC520	|= (uint16)(1 << 6);
    EIC793	|= (uint16)(1 << 6);
    EIC794	|= (uint16)(1 << 6);
    EIC795	|= (uint16)(1 << 6);
    EIC796	|= (uint16)(1 << 6);
    EIC797	|= (uint16)(1 << 6);
    EIC798	|= (uint16)(1 << 6);
    EIC799	|= (uint16)(1 << 6);
    EIC800	|= (uint16)(1 << 6);
    EIC801	|= (uint16)(1 << 6);
    EIC802	|= (uint16)(1 << 6);
    EIC803	|= (uint16)(1 << 6);
    EIC804	|= (uint16)(1 << 6);
    EIC817	|= (uint16)(1 << 6);
    EIC818	|= (uint16)(1 << 6);
    EIC819	|= (uint16)(1 << 6);
    EIC820	|= (uint16)(1 << 6);
    EIC841	|= (uint16)(1 << 6);
    EIC842	|= (uint16)(1 << 6);
    EIC960	|= (uint16)(1 << 6);
    EIC961	|= (uint16)(1 << 6);
    EIC962	|= (uint16)(1 << 6);
    EIC963	|= (uint16)(1 << 6);
    EIC964	|= (uint16)(1 << 6);
    EIC965	|= (uint16)(1 << 6);
    EIC966	|= (uint16)(1 << 6);
    EIC967	|= (uint16)(1 << 6);
    EIC968	|= (uint16)(1 << 6);
    EIC969	|= (uint16)(1 << 6);
    EIC86	  |= (uint16)(1 << 6);
    EIC102	|= (uint16)(1 << 6);
  /***********************************************************/
  /* Section 17 Standby Controller */

  /* Release the write protection of Standby controller register.*/
  MSRKCPROT = ENABLE_WRITE_KEY_CODE;

  MSR_TAUD     = 0xFFFFFFF0UL;
  MSR_ATU      = 0xFFFFFFFEUL;
  MSR_TAUJ_AWO = 0xFFFFFFFCUL;
  MSR_OSTM     = 0xFFFFFC00UL;
  MSR_GTM  = 0x00000000;
  while (MSR_GTM != 0x00000000);
  /* Enable CMU */
  GTM0CMUCLKEN = 0x00AAAAAAUL;
  /* Set the write protection of Stndby controller registers. */
  MSRKCPROT = DISABLE_WRITE_KEY_CODE;

}

void Clock_Init(void)
{
  /**********************/
  /* LSIntOSC(240[KHz]) */
  /**********************/
  /* (After power supply the LSIntOSC starts operation. It cannot be stopped.) */

  /**********************/
  /* HSIntOSC(200[MHz]) */
  /**********************/
  /* (After Power On Reset or System Reset1 release the HSIntOSC starts operation.) */

  /* Wait to HSIntOSC clock is stable(HSOSCS.HSOSCSTAB = 1). */
  while ( (HSOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* HSIntOSC stops operation in stand-by mode(HSOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /***********/
  /* MainOSC */
  /***********/

  /* 1.Confirm that the HSIntOSC is stable (HSOSCS.HSOSCSTAB = 1). */
  /* (Checked) **/

  /* 2.Confirm that the MainOSC is unstable (MOSCS.MOSCSTAB = 0). */
#if 0
  while ( (MOSCS & 0x00000002UL) != 0x00000000UL )
  {
  }
#endif

  /* 3.Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCE       = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /*******/
  /* PLL */
  /*******/

  /* 1.Confirm that the MainOSC is stable (MOSCS.MOSCSTAB = 1). */
  /* (Checked) **/

  /* 2.Confirm that the PLL is unstable (PLLS.PLLCLKSTAB = 0). */
#if 0
  while ( (PLLS & 0x00000002UL) != 0x00000000UL )
  {
  }
#endif

  /* 3.Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLE        = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the PLL has been started (PLLS.PLLCLKSTAB = 1). */
  while ( (PLLS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* PLL stops operation in stand-by mode(PLLSTPM.PLLSTPMSK = 0) */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLSTPM     = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Select a source clock(CKS_CLEANC.SYSCLKSCSID = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  /* Selected Clock source ID=0:CLK_PLLO */
  /* (This setting dependencies Option Bytes. CKDIVMD = 11B) */
  CKS_CLEANC   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm completion of selection(CKS_CLEANS.SYSCLKSACT = 0). */
  while ( (CKS_CLEANS & 0x00000001UL) != 0x00000000UL )
  {
  }
}

/* Function for the initialization of the Port pins */
void Port_Init(void)
{
  /* No Port initialization required */
}

/* Function for Watchdog settings */
void Wdg_Init(void)
{
  /* No Wdg initialization required */
}

void Reg_Init(void)
{
    volatile uint16 *ptr;
    uint32 count;
    for (count = 0; count < NUMBER_ICR_COUNT; count++)
    {
        ptr = (volatile uint16 *)RenICRADRR[count];
        *ptr = (*ptr | 0x4F);
    }
}


/*******************************************************************************
**                         Notification function                              **
*******************************************************************************/


/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
