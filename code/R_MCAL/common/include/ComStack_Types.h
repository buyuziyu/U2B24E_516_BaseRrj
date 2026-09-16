/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x, R-Car S4 MCAL Components               */
/* File name    = ComStack_Types.h                                            */
/* SW-VERSION   = 2.3.0                                                       */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c)  2023-2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for Communication Stack dependent types                          */
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
/*              Devices:        X2x/R-Car                                     */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.3.0      28/02/2025     Update SW-VERSION for
 *                           RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0      31/12/2024     Update SW-VERSION
 *                           for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1      27/06/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.3      15/04/2024     Update SW-VERSION to 2.0.3
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/
#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Std_Types.h"           /* Standard AUTOSAR types                    */
#include "ComStack_Cfg.h"        /* Definition of PduIdType and PduLengthType */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*
 * AUTOSAR specification version information
 */
#define COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION    4
#define COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION    8
#define COMSTACK_TYPES_AR_RELEASE_REVISION_VERSION 0

/*
 * File version information
 */
#define COMSTACK_TYPES_SW_MAJOR_VERSION 2
#define COMSTACK_TYPES_SW_MINOR_VERSION 3
#define COMSTACK_TYPES_SW_PATCH_VERSION 0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types (ECU dependent)                     **
*******************************************************************************/

/* SWS_COMTYPE_00036 */
typedef uint8       PNCHandleType;

/* SWS_COMTYPE_00020 */
typedef uint8        BusTrcvErrorType;

/* SWS_COMTYPE_00038 */
typedef uint8        NetworkHandleType;

/*******************************************************************************
**                      Global Data Types (ECU independent)                   **
*******************************************************************************/

/* SWS_COMTYPE_00011 */
typedef struct
{
  P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) SduDataPtr;
  P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) MetaDataPtr;
  PduLengthType  SduLength;
} PduInfoType;                   /* Basic information about a PDU of any type */

/* SWS_COMTYPE_00031 */
typedef enum
{
  TP_STMIN,
  TP_BS,
  TP_BC
} TPParameterType;     /* Specify parameter to which value has to be changed */

/* SWS_COMTYPE_00012 */
typedef enum
{
  BUFREQ_OK,
  BUFREQ_E_NOT_OK,
  BUFREQ_E_BUSY,
  BUFREQ_E_OVFL
} BufReq_ReturnType;                 /* result of a buffer request */

/* SWS_COMTYPE_00027 */
typedef enum
{
  TP_DATACONF,
  TP_DATARETRY,
  TP_CONFPENDING
} TpDataStateType; /* Variables of this type shall be used to store the */
                   /* state of TP buffer */
/* SWS_COMTYPE_00037 */
typedef struct
{
  TpDataStateType TpDataState;
  PduLengthType TxTpDataCnt;
} RetryInfoType;  /* Variables of this type shall be used to store the */
                  /* information about Tp buffer handling. */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* COMSTACK_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
