/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_Version.c                                                                                       */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains code for version checking for modules included by PWM                                           */
/* Driver                                                                                                             */
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
** 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
** 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
** 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
** 1.3.2: 04/08/2021 : Format source code unified within module.                                                      **
** 1.3.1: 02/07/2021 : Format source code to 120 characters                                                           **
**        15/05/2021 : Fixed Coding Rule and tailor space                                                             **
** 1.2.0: 28/07/2020 : Release                                                                                        **
** 1.1.0: 19/06/2020 : Release                                                                                        **
** 1.0.0: 24/03/2020 : Initial Version.                                                                               **
**                                                                                                                    */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Pwm module version information and other modules version information */
#include "Pwm.h"
#include "Pwm_Version.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_VERSION_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_VERSION_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_VERSION_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE
/* Module software version information */
#define PWM_VERSION_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_VERSION_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (PWM_VERSION_AR_RELEASE_MAJOR_VERSION != PWM_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_Version.c : Mismatch in Release Major Version"
#endif
#if (PWM_VERSION_AR_RELEASE_MINOR_VERSION != PWM_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_Version.c : Mismatch in Release Minor Version"
#endif
#if (PWM_VERSION_AR_RELEASE_REVISION_VERSION != PWM_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_Version.c : Mismatch in Release Revision Version"
#endif
#if (PWM_VERSION_SW_MAJOR_VERSION != PWM_VERSION_C_SW_MAJOR_VERSION)
  #error "Pwm_Version.c : Mismatch in Software Major Version"
#endif
#if (PWM_VERSION_SW_MINOR_VERSION != PWM_VERSION_C_SW_MINOR_VERSION)
  #error "Pwm_Version.c : Mismatch in Software Minor Version"
#endif


#if (PWM_VERSION_CHECK_EXT_MODULES == STD_ON)

#if ((DEM_AR_RELEASE_MAJOR_VERSION != PWM_AR_RELEASE_MAJOR_VERSION) \
  || (DEM_AR_RELEASE_MINOR_VERSION != PWM_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif /* End of DEM */

#if (PWM_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != PWM_AR_RELEASE_MAJOR_VERSION) \
  || (DET_AR_RELEASE_MINOR_VERSION != PWM_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif /* End of DET */
#endif /* End of PWM_DEV_ERROR_DETECT */

#if ((OS_AR_RELEASE_MAJOR_VERSION != PWM_AR_RELEASE_MAJOR_VERSION) \
  || (OS_AR_RELEASE_MINOR_VERSION != PWM_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif /* End of OS */

#if (PWM_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != PWM_AR_RELEASE_MAJOR_VERSION) \
  || (RTE_AR_RELEASE_MINOR_VERSION != PWM_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif /* End of RTE */
#endif /* End of PWM_CRITICAL_SECTION_PROTECTION */

#endif /* End of PWM_VERSION_CHECK_EXT_MODULES */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
