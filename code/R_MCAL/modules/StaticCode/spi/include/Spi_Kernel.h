/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Spi_Kernel.h                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2023-2025 Renesas Electronics Corporation.                                                            */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *  2.1.3  31/10/2024  : Update SW-VERSION up to 2.1.3
 *  2.1.2  30/09/2024  : Update SW-VERSION up to 2.1.2
 *  2.1.1  21/06/2024  : Update conditions for the preprocessor Spi_Kernel_Cancel and Spi_Kernel_ForceCancel
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534, 1536
 *  2.1.0  27/02/2024  : Update SW-VERSION to 2.1.0
 *  2.0.2  14/12/2023  : Update SW-VERSION to 2.0.2
 *  2.0.0  04/04/2023  : Initial Version
 *  2.0.1  23/10/2023  : Update QAC message 1534, 1536 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 */
/**********************************************************************************************************************/
#ifndef SPI_KERNEL_H
#define SPI_KERNEL_H
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_KERNEL_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_KERNEL_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_KERNEL_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* Module Software version information */
#define SPI_KERNEL_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_KERNEL_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION
#define SPI_KERNEL_SW_PATCH_VERSION            SPI_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (SPI_MULTI_CORE_SUPPORT == STD_ON)
/* Satellite service */
#define Spi_LockedStatus(x)                    (x == SPI_TRUE)
#define Spi_UnLockedStatus(x)                  (x == SPI_FALSE)

/* Master serivce */
#define Spi_CheckingRequest(x)                 (x == SPI_TRUE)
#define Spi_LockProcess(x)                     (x = SPI_TRUE)
#define Spi_UnLockProcess(x)                   (x = SPI_FALSE)

/* Type definition for Request from Async Transmit */
typedef struct Spi_AsyncTransmit_Request_Stag
{
    /* Satellite request */
    boolean blSetRequest;
} Spi_AsyncTransmit_RequestType;

/* Type definition for Request from Sync Transmit */
typedef struct Spi_SyncTransmit_Request_Stag
{
    /* Satellite request */
    boolean blSetRequest;
    /* Sync transmit result */
    Std_ReturnType ucResult;
} Spi_SyncTransmit_RequestType;

/* Type definition for Request from Cancel Transmit */
typedef struct Spi_CancelTransmit_Request_Stag
{
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Spi_CancelTransmit_RequestType;

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/* Globale scope - share among cores */
#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

/* Sync and Async transmit request */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
extern volatile VAR(Spi_AsyncTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaAsyncTransmitInfo[SPI_MAX_SEQUENCE];
#endif
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
extern volatile VAR(Spi_SyncTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaSyncTransmitInfo[SPI_MAX_SEQUENCE];
#endif
/* Cancel transmit request */
#if (SPI_CANCEL_API == STD_ON)
extern volatile VAR(Spi_CancelTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaCancelTransmitInfo[SPI_MAX_SEQUENCE];
#endif
#if (SPI_FORCE_CANCEL_API == STD_ON)
extern volatile VAR(Spi_CancelTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaForceCancelTransmitInfo[SPI_MAX_SEQUENCE];
#endif

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define SPI_START_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_AsyncTransmit(void);
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_SyncTransmit(void);
#endif

#if ((SPI_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_Cancel(void);
#endif

#if ((SPI_FORCE_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_ForceCancel(void);
#endif

#define SPI_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"

#endif /* SPI_MULTI_CORE_SUPPORT == STD_ON */
#endif /* Spi_KERNEL_H */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
