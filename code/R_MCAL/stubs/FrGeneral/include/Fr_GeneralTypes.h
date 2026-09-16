/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Fr_GeneralTypes.h                                           */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file consists of types specified within Fr Driver and FrTrcv          */
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
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1      30/06/2025     Remove SW-VERSION in file header
 * 2.4.0      30/06/2025     Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2      29/04/2025     Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1      31/03/2025     Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0      28/02/2025     Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1      31/12/2024     Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0      31/12/2024     Update SW-VERSION
 *                           for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3      31/10/2024     Update SW-VERSION to 2.1.3
 * 2.1.1      24/07/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/

#ifndef FR_GENERAL_TYPES              /* Protected against multiple inclusion */
#define FR_GENERAL_TYPES

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define FR_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION       4U
#define FR_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION       8U
#define FR_GENERAL_TYPES_AR_RELEASE_REVISION_VERSION    0U

/* Software Version Information */
#define FR_GENERAL_TYPES_SW_MAJOR_VERSION               2U
#define FR_GENERAL_TYPES_SW_MINOR_VERSION               4U
#define FR_GENERAL_TYPES_SW_PATCH_VERSION               1U

/*******************************************************************************
**                      Type definitions                                      **
*******************************************************************************/

#define  FR_CIDX_GDCYCLE                         0U
#define  FR_CIDX_PMICROPERCYCLE                  1U
#define  FR_CIDX_PDLISTENTIMEOUT                 2U
#define  FR_CIDX_GMACROPERCYCLE                  3U
#define  FR_CIDX_GDMACROTICK                     4U
#define  FR_CIDX_GNUMBEROFMINISLOTS              5U
#define  FR_CIDX_GNUMBEROFSTATICSLOTS            6U
#define  FR_CIDX_GDNIT                           7U
#define  FR_CIDX_GDSTATICSLOT                    8U
#define  FR_CIDX_GDWAKEUPRXWINDOW                9U
#define  FR_CIDX_PKEYSLOTID                      10U
#define  FR_CIDX_PLATESTTX                       11U
#define  FR_CIDX_POFFSETCORRECTIONOUT            12U
#define  FR_CIDX_POFFSETCORRECTIONSTART          13U
#define  FR_CIDX_PRATECORRECTIONOUT              14U
#define  FR_CIDX_PSECONDKEYSLOTID                15U
#define  FR_CIDX_PDACCEPTEDSTARTUPRANGE          16U
#define  FR_CIDX_GCOLDSTARTATTEMPTS              17U
#define  FR_CIDX_GCYCLECOUNTMAX                  18U
#define  FR_CIDX_GLISTENNOISE                    19U
#define  FR_CIDX_GMAXWITHOUTCLOCKCORRECTFATAL    20U
#define  FR_CIDX_GMAXWITHOUTCLOCKCORRECTPASSIVE  21U
#define  FR_CIDX_GNETWORKMANAGEMENTVECTORLENGTH  22U
#define  FR_CIDX_GPAYLOADLENGTHSTATIC            23U
#define  FR_CIDX_GSYNCFRAMEIDCOUNTMAX            24U
#define  FR_CIDX_GDACTIONPOINTOFFSET             25U
#define  FR_CIDX_GDBIT                           26U
#define  FR_CIDX_GDCASRXLOWMAX                   27U
#define  FR_CIDX_GDDYNAMICSLOTIDLEPHASE          28U
#define  FR_CIDX_GDMINISLOTACTIONPOINTOFFSET     29U
#define  FR_CIDX_GDMINISLOT                      30U
#define  FR_CIDX_GDSAMPLECLOCKPERIOD             31U
#define  FR_CIDX_GDSYMBOLWINDOW                  32U
#define  FR_CIDX_GDSYMBOLWINDOWACTIONPOINTOFFSET 33U
#define  FR_CIDX_GDTSSTRANSMITTER                34U
#define  FR_CIDX_GDWAKEUPRXIDLE                  35U
#define  FR_CIDX_GDWAKEUPRXLOW                   36U
#define  FR_CIDX_GDWAKEUPTXACTIVE                37U
#define  FR_CIDX_GDWAKEUPTXIDLE                  38U
#define  FR_CIDX_PALLOWPASSIVETOACTIVE           39U
#define  FR_CIDX_PCHANNELS                       40U
#define  FR_CIDX_PCLUSTERDRIFTDAMPING            41U
#define  FR_CIDX_PDECODINGCORRECTION             42U
#define  FR_CIDX_PDELAYCOMPENSATIONA             43U
#define  FR_CIDX_PDELAYCOMPENSATIONB             44U
#define  FR_CIDX_PMACROINITIALOFFSETA            45U
#define  FR_CIDX_PMACROINITIALOFFSETB            46U
#define  FR_CIDX_PMICROINITIALOFFSETA            47U
#define  FR_CIDX_PMICROINITIALOFFSETB            48U
#define  FR_CIDX_PPAYLOADLENGTHDYNMAX            49U
#define  FR_CIDX_PSAMPLESPERMICROTICK            50U
#define  FR_CIDX_PWAKEUPCHANNEL                  51U
#define  FR_CIDX_PWAKEUPPATTERN                  52U
#define  FR_CIDX_PDMICROTICK                     53U
#define  FR_CIDX_GDIGNOREAFTERTX                 54U
#define  FR_CIDX_PALLOWHALTDUETOCLOCK            55U
#define  FR_CIDX_PEXTERNALSYNC                   56U
#define  FR_CIDX_PFALLBACKINTERNAL               57U
#define  FR_CIDX_PKEYSLOTONLYENABLED             58U
#define  FR_CIDX_PKEYSLOTUSEDFORSTARTUP          59U
#define  FR_CIDX_PKEYSLOTUSEDFORSYNC             60U
#define  FR_CIDX_PNMVECTOREARLYUPDATE            61U
#define  FR_CIDX_PTWOKEYSLOTMODE                 62U

/*******************************************************************************
**                      Fr_POCStateType                                       **
*******************************************************************************/
typedef enum ETag_Fr_POCStateType
{
   FR_POCSTATE_CONFIG         = 0x00,
   FR_POCSTATE_DEFAULT_CONFIG = 0x01,
   FR_POCSTATE_HALT           = 0x02,
   FR_POCSTATE_NORMAL_ACTIVE  = 0x03,
   FR_POCSTATE_NORMAL_PASSIVE = 0x04,
   FR_POCSTATE_READY          = 0x05,
   FR_POCSTATE_STARTUP        = 0x06,
   FR_POCSTATE_WAKEUP         = 0x07
} Fr_POCStateType;

/*******************************************************************************
**                      Fr_SlotModeType                                       **
*******************************************************************************/
typedef enum ETag_Fr_SlotModeType
{
   FR_SLOTMODE_KEYSLOT     = 0x00,
   FR_SLOTMODE_ALL_PENDING = 0x01,
   FR_SLOTMODE_ALL         = 0x02
} Fr_SlotModeType;

/*******************************************************************************
**                      Fr_ErrorModeType                                      **
*******************************************************************************/
typedef enum ETag_Fr_ErrorModeType
{
   FR_ERRORMODE_ACTIVE    = 0x00,
   FR_ERRORMODE_PASSIVE   = 0x01,
   FR_ERRORMODE_COMM_HALT = 0x02
} Fr_ErrorModeType;

/*******************************************************************************
**                      Fr_WakeupStatusType                                   **
*******************************************************************************/
typedef enum ETag_Fr_WakeupStatusType
{
   FR_WAKEUP_UNDEFINED          = 0x00,
   FR_WAKEUP_RECEIVED_HEADER    = 0x01,
   FR_WAKEUP_RECEIVED_WUP       = 0x02,
   FR_WAKEUP_COLLISION_HEADER   = 0x03,
   FR_WAKEUP_COLLISION_WUP      = 0x04,
   FR_WAKEUP_COLLISION_UNKNOWN  = 0x05,
   FR_WAKEUP_TRANSMITTED        = 0x06
} Fr_WakeupStatusType;

/*******************************************************************************
**                      Fr_StartupStateType                                   **
*******************************************************************************/
typedef enum ETag_Fr_StartupStateType
{
   FR_STARTUP_UNDEFINED                      = 0x00,
   FR_STARTUP_COLDSTART_LISTEN               = 0x01,
   FR_STARTUP_INTEGRATION_COLDSTART_CHECK    = 0x02,
   FR_STARTUP_COLDSTART_JOIN                 = 0x03,
   FR_STARTUP_COLDSTART_COLLISION_RESOLUTION = 0x04,
   FR_STARTUP_COLDSTART_CONSISTENCY_CHECK    = 0x05,
   FR_STARTUP_INTEGRATION_LISTEN             = 0x06,
   FR_STARTUP_INITIALIZE_SCHEDULE            = 0x07,
   FR_STARTUP_INTEGRATION_CONSISTENCY_CHECK  = 0x08,
   FR_STARTUP_COLDSTART_GAP                  = 0x09,
   FR_STARTUP_EXTERNAL_STARTUP               = 0x0A
} Fr_StartupStateType;

/*******************************************************************************
**                      Fr_POCStatusType                                      **
*******************************************************************************/
typedef  struct STag_Fr_POCStatusType
{
  boolean                CHIHaltRequest;
  boolean                ColdstartNoise;
  Fr_ErrorModeType    ErrorMode;
  boolean                Freeze;
  Fr_SlotModeType     SlotMode;
  Fr_StartupStateType StartupState;
  Fr_POCStateType     State;
  Fr_WakeupStatusType WakeupStatus;
  boolean                CHIReadyRequest;
} Fr_POCStatusType;

/*******************************************************************************
**                      Fr_TxLPduStatusType                                   **
*******************************************************************************/
typedef enum ETag_Fr_TxLPduStatusType
{
   FR_TRANSMITTED          = 0x00,
   FR_TRANSMITTED_CONFLICT = 0x01,
   FR_NOT_TRANSMITTED      = 0x02,
} Fr_TxLPduStatusType;

/*******************************************************************************
**                      Fr_RxLPduStatusType                                   **
*******************************************************************************/
typedef enum ETag_Fr_RxLPduStatusType
{
   FR_RECEIVED                     = 0x00,
   FR_NOT_RECEIVED                 = 0x01,
   FR_RECEIVED_MORE_DATA_AVAILABLE = 0x02
} Fr_RxLPduStatusType;

/*******************************************************************************
**                      Fr_ChannelType                                        **
*******************************************************************************/
typedef enum ETag_Fr_ChannelType
{
   FR_CHANNEL_A  = 0x01,
   FR_CHANNEL_B  = 0x02,
   FR_CHANNEL_AB = 0x03
} Fr_ChannelType;
/*******************************************************************************
**                      Fr_MTSStatusType                                      **
**                      LOWER VERSION                                         **
*******************************************************************************/
typedef enum ETag_Fr_MTSStatusType
{
   FR_MTS_RCV = 0,
   FR_MTS_RCV_SYNERR,
   FR_MTS_RCV_BVIO,
   FR_MTS_RCV_SYNERR_BVIO,
   FR_MTS_NOT_RCV,
   FR_MTS_NOT_RCV_SYNERR,
   FR_MTS_NOT_RCV_BVIO,
   FR_MTS_NOT_RCV_SYNERR_BVIO
} Fr_MTSStatusType;
/*******************************************************************************
**                     Fr_OffsetCorrectionType                                **
**                      LOWER VERSION                                         **
*******************************************************************************/
typedef enum ETag_Fr_OffsetCorrectionType
{
   FR_OFFSET_INC = 0,
   FR_OFFSET_DEC,
   FR_OFFSET_NOCHANGE
} Fr_OffsetCorrectionType;
/*******************************************************************************
**                     Fr_RateCorrectionType                                  **
**                      LOWER VERSION                                         **
*******************************************************************************/
typedef enum ETag_Fr_RateCorrectionType
{
   FR_RATE_INC = 0,
   FR_RATE_DEC,
   FR_RATE_NOCHANGE
} Fr_RateCorrectionType;
/******************************************************************************/

/*******************************************************************************
**                      Fr_SyncStateType                                      **
*******************************************************************************/
typedef enum ETag_Fr_SyncStateType
{
   FR_ASYNC = 0,
   FR_SYNC
} Fr_SyncStateType;

/*******************************************************************************
**                      Fr_HWConsistencyModeType                              **
*******************************************************************************/
/* Type definition for Fr_HWConsistencyModeType */
typedef enum ETag_Fr_HWConsistencyModeType
{
  FR_STATIC = 0,
  FR_DYNAMIC
}Fr_HWConsistencyModeType;

/*******************************************************************************
**                      Fr_SlotAssignmentType                              **
*******************************************************************************/
typedef struct STag_Fr_SlotAssignmentType 
{
  uint8          Cycle;
  uint16         SlotId;
  Fr_ChannelType channelId;
}Fr_SlotAssignmentType;
#endif  /* FR_GENERAL_TYPES */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
