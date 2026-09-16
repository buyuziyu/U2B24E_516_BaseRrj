/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port_Cfg.h                                                                                          */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains pre-compile time parameters.                                                                    */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                                         */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
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
/*              Devices:        R7F7025BxFABC                                                                         */
/*====================================================================================================================*/


/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Generation Tool Version                                                                       **
***********************************************************************************************************************/
/*                                                                                                                    */
/* TOOL VERSION:  PortU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                       */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\port\generator\U2B24-E\R2211_port_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_port.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_port.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_port.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:57
 */


#ifndef PORT_CFG_H
#define PORT_CFG_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION                                       4U
#define PORT_CFG_AR_RELEASE_MINOR_VERSION                                       8U
#define PORT_CFG_AR_RELEASE_REVISION_VERSION                                    0U
#define PORT_CFG_SW_MAJOR_VERSION                                               2U
#define PORT_CFG_SW_MINOR_VERSION                                               4U
#define PORT_AR_VERSION                                                         PORT_AR_R22_11_VERSION

/***********************************************************************************************************************
**                      Common Published Information                                                                  **
***********************************************************************************************************************/
#define PORT_AR_RELEASE_MAJOR_VERSION_VALUE                                     4U
#define PORT_AR_RELEASE_MINOR_VERSION_VALUE                                     8U
#define PORT_AR_RELEASE_REVISION_VERSION_VALUE                                  0U
#define PORT_SW_MAJOR_VERSION_VALUE                                             2U
#define PORT_SW_MINOR_VERSION_VALUE                                             4U
#define PORT_SW_PATCH_VERSION_VALUE                                             1U
#define PORT_VENDOR_ID_VALUE                                                    59U
#define PORT_MODULE_ID_VALUE                                                    124U

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/
/* Instance ID of the PORT Driver Component */
#define PORT_INSTANCE_ID_VALUE                                                  0U

/* DEM for Port Driver component */
#define PORT_E_WRITE_TIMEOUT_FAILURE                                            \
                                                                             DemConf_DemEventParameter_DemEventParameter

/* Enables/Disables Development error detect */
#define PORT_DEV_ERROR_DETECT                                                   STD_ON

/* Enables/Disables Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API                                              STD_ON

/* Enables/Disables Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API                                                   STD_ON

/* Enables/Disables Port_GetVersionInfo API */
#define PORT_VERSION_INFO_API                                                   STD_ON

/* Enables/Disables Port_SetPinDefaultDirection API */
#define PORT_SET_PIN_DEFAULT_DIRECTION_API                                      STD_ON

/* Enable/Disable the enter/exit critical section functionality */
#define PORT_CRITICAL_SECTION_PROTECTION                                        STD_ON

/* Pre-compile option to enable or disable version check of inter-module dependencies */
#define PORT_VERSION_CHECK_EXT_MODULES                                          STD_ON

/* Enables/Disables Port_SetToDioMode and Port_SetToAlternateMode API */
#define PORT_SET_TO_DIO_ALT_MODE_API                                            STD_ON

/* Enables/Disables JTAG For Debugging */
#define PORT_JTAG_DEBUGGING                                                     STD_ON

/* Enables/Disables Port_EcmMaskERRORIN and Port_EcmClearERRORIN API */
#define PORT_ECM_ERRORIN_API                                                    STD_ON

/* Multicore support */
#define PORT_MULTI_CORE_SUPPORT                                                 STD_ON

/* Availability of register DNFP02 */
#define PORT_DNFP02EDC16_AVAILABLE                                              STD_ON

/* Availability of register DNFP03 */
#define PORT_DNFP03_AVAILABLE                                                   STD_ON

/* Register setting check count */
#define PORT_REG_CHK_CNT                                                        50

/* Indicates the number of Alternative Modes */
#define PORT_MAX_MODE                                                           (uint8)0x10U

/* Availability of U2Bx/U2BxE register */
#define PORT_DEVICE_SUPPORT                                                     STD_ON

/* Register value for setting Pull Up Pull Down Voltage */
#define PORT_PU_PD_VOLTAGE                                                      (uint16)0x0000U

/* Enables/Disables report write failure production error */
#define PORT_E_WRITE_TIMEOUT_FAILURE_CONFIGURED                                 STD_OFF

/* Availability of Input PortGroup */
#define PORT_GROUP_INPUT_AVAILABLE                                              STD_OFF


/* Port Pin Handles */
#define PortConf_PortGroup0_PortPin0                                            (Port_PinType)0
#define PortConf_PortGroup0_PortPin1                                            (Port_PinType)1
#define PortConf_PortGroup0_PortPin2                                            (Port_PinType)2
#define PortConf_PortGroup0_PortPin3                                            (Port_PinType)3
#define PortConf_PortGroup0_PortPin4                                            (Port_PinType)4
#define PortConf_PortGroup0_PortPin5                                            (Port_PinType)5
#define PortConf_PortGroup0_PortPin6                                            (Port_PinType)6
#define PortConf_PortGroup0_PortPin7                                            (Port_PinType)7
#define PortConf_PortGroup0_PortPin8                                            (Port_PinType)8
#define PortConf_PortGroup0_PortPin9                                            (Port_PinType)9
#define PortConf_PortGroup0_PortPin10                                           (Port_PinType)10
#define PortConf_PortGroup0_PortPin11                                           (Port_PinType)11
#define PortConf_PortGroup0_PortPin12                                           (Port_PinType)12
#define PortConf_PortGroup0_PortPin13                                           (Port_PinType)13
#define PortConf_PortGroup0_PortPin14                                           (Port_PinType)14
#define PortConf_PortGroup0_PortPin15                                           (Port_PinType)15
#define PortConf_PortGroup1_PortPin0                                            (Port_PinType)16
#define PortConf_PortGroup1_PortPin1                                            (Port_PinType)17
#define PortConf_PortGroup1_PortPin2                                            (Port_PinType)18
#define PortConf_PortGroup1_PortPin7                                            (Port_PinType)19
#define PortConf_PortGroup1_PortPin8                                            (Port_PinType)20
#define PortConf_PortGroup1_PortPin9                                            (Port_PinType)21
#define PortConf_PortGroup1_PortPin10                                           (Port_PinType)22
#define PortConf_PortGroup1_PortPin11                                           (Port_PinType)23
#define PortConf_PortGroup1_PortPin12                                           (Port_PinType)24
#define PortConf_PortGroup1_PortPin13                                           (Port_PinType)25
#define PortConf_PortGroup1_PortPin14                                           (Port_PinType)26
#define PortConf_PortGroup1_PortPin15                                           (Port_PinType)27
#define PortConf_PortGroup2_PortPin0                                            (Port_PinType)28
#define PortConf_PortGroup2_PortPin1                                            (Port_PinType)29
#define PortConf_PortGroup2_PortPin2                                            (Port_PinType)30
#define PortConf_PortGroup2_PortPin3                                            (Port_PinType)31
#define PortConf_PortGroup2_PortPin4                                            (Port_PinType)32
#define PortConf_PortGroup2_PortPin5                                            (Port_PinType)33
#define PortConf_PortGroup2_PortPin6                                            (Port_PinType)34
#define PortConf_PortGroup2_PortPin7                                            (Port_PinType)35
#define PortConf_PortGroup2_PortPin8                                            (Port_PinType)36
#define PortConf_PortGroup2_PortPin12                                           (Port_PinType)37
#define PortConf_PortGroup2_PortPin13                                           (Port_PinType)38
#define PortConf_PortGroup2_PortPin14                                           (Port_PinType)39
#define PortConf_PortGroup2_PortPin15                                           (Port_PinType)40
#define PortConf_PortGroup3_PortPin0                                            (Port_PinType)41
#define PortConf_PortGroup3_PortPin2                                            (Port_PinType)42
#define PortConf_PortGroup3_PortPin3                                            (Port_PinType)43
#define PortConf_PortGroup10_PortPin0                                           (Port_PinType)44
#define PortConf_PortGroup10_PortPin1                                           (Port_PinType)45
#define PortConf_PortGroup10_PortPin2                                           (Port_PinType)46
#define PortConf_PortGroup10_PortPin3                                           (Port_PinType)47
#define PortConf_PortGroup10_PortPin4                                           (Port_PinType)48
#define PortConf_PortGroup10_PortPin5                                           (Port_PinType)49
#define PortConf_PortGroup10_PortPin6                                           (Port_PinType)50
#define PortConf_PortGroup10_PortPin7                                           (Port_PinType)51
#define PortConf_PortGroup10_PortPin8                                           (Port_PinType)52
#define PortConf_PortGroup10_PortPin9                                           (Port_PinType)53
#define PortConf_PortGroup10_PortPin10                                          (Port_PinType)54
#define PortConf_PortGroup10_PortPin11                                          (Port_PinType)55
#define PortConf_PortGroup10_PortPin12                                          (Port_PinType)56
#define PortConf_PortGroup10_PortPin13                                          (Port_PinType)57
#define PortConf_PortGroup10_PortPin14                                          (Port_PinType)58
#define PortConf_PortGroup10_PortPin15                                          (Port_PinType)59
#define PortConf_PortGroup11_PortPin0                                           (Port_PinType)60
#define PortConf_PortGroup11_PortPin1                                           (Port_PinType)61
#define PortConf_PortGroup11_PortPin2                                           (Port_PinType)62
#define PortConf_PortGroup11_PortPin3                                           (Port_PinType)63
#define PortConf_PortGroup11_PortPin4                                           (Port_PinType)64
#define PortConf_PortGroup11_PortPin5                                           (Port_PinType)65
#define PortConf_PortGroup11_PortPin6                                           (Port_PinType)66
#define PortConf_PortGroup11_PortPin7                                           (Port_PinType)67
#define PortConf_PortGroup11_PortPin8                                           (Port_PinType)68
#define PortConf_PortGroup11_PortPin9                                           (Port_PinType)69
#define PortConf_PortGroup11_PortPin10                                          (Port_PinType)70
#define PortConf_PortGroup11_PortPin11                                          (Port_PinType)71
#define PortConf_PortGroup11_PortPin12                                          (Port_PinType)72
#define PortConf_PortGroup11_PortPin13                                          (Port_PinType)73
#define PortConf_PortGroup11_PortPin14                                          (Port_PinType)74
#define PortConf_PortGroup11_PortPin15                                          (Port_PinType)75
#define PortConf_PortGroup12_PortPin0                                           (Port_PinType)76
#define PortConf_PortGroup12_PortPin1                                           (Port_PinType)77
#define PortConf_PortGroup13_PortPin0                                           (Port_PinType)78
#define PortConf_PortGroup13_PortPin1                                           (Port_PinType)79
#define PortConf_PortGroup13_PortPin2                                           (Port_PinType)80
#define PortConf_PortGroup13_PortPin3                                           (Port_PinType)81
#define PortConf_PortGroup13_PortPin4                                           (Port_PinType)82
#define PortConf_PortGroup13_PortPin5                                           (Port_PinType)83
#define PortConf_PortGroup13_PortPin6                                           (Port_PinType)84
#define PortConf_PortGroup13_PortPin7                                           (Port_PinType)85
#define PortConf_PortGroup13_PortPin9                                           (Port_PinType)86
#define PortConf_PortGroup13_PortPin10                                          (Port_PinType)87
#define PortConf_PortGroup13_PortPin11                                          (Port_PinType)88
#define PortConf_PortGroup13_PortPin12                                          (Port_PinType)89
#define PortConf_PortGroup13_PortPin13                                          (Port_PinType)90
#define PortConf_PortGroup13_PortPin14                                          (Port_PinType)91
#define PortConf_PortGroup13_PortPin15                                          (Port_PinType)92
#define PortConf_PortGroup14_PortPin0                                           (Port_PinType)93
#define PortConf_PortGroup14_PortPin1                                           (Port_PinType)94
#define PortConf_PortGroup14_PortPin2                                           (Port_PinType)95
#define PortConf_PortGroup14_PortPin3                                           (Port_PinType)96
#define PortConf_PortGroup14_PortPin4                                           (Port_PinType)97
#define PortConf_PortGroup14_PortPin5                                           (Port_PinType)98
#define PortConf_PortGroup14_PortPin6                                           (Port_PinType)99
#define PortConf_PortGroup14_PortPin7                                           (Port_PinType)100
#define PortConf_PortGroup14_PortPin8                                           (Port_PinType)101
#define PortConf_PortGroup14_PortPin9                                           (Port_PinType)102
#define PortConf_PortGroup14_PortPin10                                          (Port_PinType)103
#define PortConf_PortGroup14_PortPin11                                          (Port_PinType)104
#define PortConf_PortGroup14_PortPin12                                          (Port_PinType)105
#define PortConf_PortGroup14_PortPin13                                          (Port_PinType)106
#define PortConf_PortGroup14_PortPin14                                          (Port_PinType)107
#define PortConf_PortGroup14_PortPin15                                          (Port_PinType)108
#define PortConf_PortGroup15_PortPin0                                           (Port_PinType)109
#define PortConf_PortGroup15_PortPin1                                           (Port_PinType)110
#define PortConf_PortGroup15_PortPin2                                           (Port_PinType)111
#define PortConf_PortGroup15_PortPin3                                           (Port_PinType)112
#define PortConf_PortGroup15_PortPin4                                           (Port_PinType)113
#define PortConf_PortGroup15_PortPin5                                           (Port_PinType)114
#define PortConf_PortGroup15_PortPin6                                           (Port_PinType)115
#define PortConf_PortGroup15_PortPin7                                           (Port_PinType)116
#define PortConf_PortGroup15_PortPin8                                           (Port_PinType)117
#define PortConf_PortGroup15_PortPin9                                           (Port_PinType)118
#define PortConf_PortGroup15_PortPin14                                          (Port_PinType)119
#define PortConf_PortGroup15_PortPin15                                          (Port_PinType)120
#define PortConf_PortGroup16_PortPin10                                          (Port_PinType)121
#define PortConf_PortGroup16_PortPin11                                          (Port_PinType)122
#define PortConf_PortGroup16_PortPin12                                          (Port_PinType)123
#define PortConf_PortGroup16_PortPin13                                          (Port_PinType)124
#define PortConf_PortGroup20_PortPin0                                           (Port_PinType)125
#define PortConf_PortGroup20_PortPin3                                           (Port_PinType)126
#define PortConf_PortGroup20_PortPin6                                           (Port_PinType)127
#define PortConf_PortGroup20_PortPin7                                           (Port_PinType)128
#define PortConf_PortGroup20_PortPin8                                           (Port_PinType)129
#define PortConf_PortGroup20_PortPin9                                           (Port_PinType)130
#define PortConf_PortGroup20_PortPin10                                          (Port_PinType)131
#define PortConf_PortGroup20_PortPin11                                          (Port_PinType)132
#define PortConf_PortGroup20_PortPin12                                          (Port_PinType)133
#define PortConf_PortGroup20_PortPin13                                          (Port_PinType)134
#define PortConf_PortGroup20_PortPin14                                          (Port_PinType)135
#define PortConf_PortGroup21_PortPin0                                           (Port_PinType)136
#define PortConf_PortGroup21_PortPin1                                           (Port_PinType)137
#define PortConf_PortGroup21_PortPin2                                           (Port_PinType)138
#define PortConf_PortGroup21_PortPin3                                           (Port_PinType)139
#define PortConf_PortGroup21_PortPin4                                           (Port_PinType)140
#define PortConf_PortGroup21_PortPin5                                           (Port_PinType)141
#define PortConf_PortGroup22_PortPin0                                           (Port_PinType)142
#define PortConf_PortGroup22_PortPin1                                           (Port_PinType)143
#define PortConf_PortGroup22_PortPin2                                           (Port_PinType)144
#define PortConf_PortGroup22_PortPin3                                           (Port_PinType)145
#define PortConf_PortGroup22_PortPin4                                           (Port_PinType)146
#define PortConf_PortGroup22_PortPin5                                           (Port_PinType)147
#define PortConf_PortGroup22_PortPin6                                           (Port_PinType)148
#define PortConf_PortGroup22_PortPin7                                           (Port_PinType)149
#define PortConf_PortGroup22_PortPin8                                           (Port_PinType)150
#define PortConf_PortGroup22_PortPin9                                           (Port_PinType)151
#define PortConf_PortGroup22_PortPin10                                          (Port_PinType)152
#define PortConf_PortGroup22_PortPin11                                          (Port_PinType)153
#define PortConf_PortGroup23_PortPin0                                           (Port_PinType)154
#define PortConf_PortGroup23_PortPin1                                           (Port_PinType)155
#define PortConf_PortGroup23_PortPin2                                           (Port_PinType)156
#define PortConf_PortGroup23_PortPin3                                           (Port_PinType)157
#define PortConf_PortGroup23_PortPin4                                           (Port_PinType)158
#define PortConf_PortGroup23_PortPin6                                           (Port_PinType)159
#define PortConf_PortGroup23_PortPin7                                           (Port_PinType)160
#define PortConf_PortGroup24_PortPin0                                           (Port_PinType)161
#define PortConf_PortGroup24_PortPin1                                           (Port_PinType)162
#define PortConf_PortGroup24_PortPin2                                           (Port_PinType)163
#define PortConf_PortGroup24_PortPin3                                           (Port_PinType)164
#define PortConf_PortGroup24_PortPin4                                           (Port_PinType)165
#define PortConf_PortGroup24_PortPin5                                           (Port_PinType)166
#define PortConf_PortGroup24_PortPin6                                           (Port_PinType)167
#define PortConf_PortGroup24_PortPin7                                           (Port_PinType)168
#define PortConf_PortGroup24_PortPin8                                           (Port_PinType)169
#define PortConf_PortGroup24_PortPin9                                           (Port_PinType)170
#define PortConf_PortGroup24_PortPin10                                          (Port_PinType)171
#define PortConf_PortGroup24_PortPin11                                          (Port_PinType)172
#define PortConf_PortGroup24_PortPin12                                          (Port_PinType)173
#define PortConf_PortGroup24_PortPin13                                          (Port_PinType)174
#define PortConf_PortGroup24_PortPin14                                          (Port_PinType)175
#define PortConf_PortGroup24_PortPin15                                          (Port_PinType)176
#define PortConf_PortGroup25_PortPin0                                           (Port_PinType)177
#define PortConf_PortGroup25_PortPin1                                           (Port_PinType)178
#define PortConf_PortGroup25_PortPin2                                           (Port_PinType)179
#define PortConf_PortGroup25_PortPin3                                           (Port_PinType)180
#define PortConf_PortGroup25_PortPin4                                           (Port_PinType)181
#define PortConf_PortGroup25_PortPin5                                           (Port_PinType)182
#define PortConf_PortGroup25_PortPin6                                           (Port_PinType)183
#define PortConf_PortGroup25_PortPin7                                           (Port_PinType)184
#define PortConf_PortGroup25_PortPin8                                           (Port_PinType)185
#define PortConf_PortGroup25_PortPin9                                           (Port_PinType)186
#define PortConf_PortGroup25_PortPin10                                          (Port_PinType)187
#define PortConf_PortGroup25_PortPin11                                          (Port_PinType)188
#define PortConf_PortGroup25_PortPin12                                          (Port_PinType)189
#define PortConf_PortGroup25_PortPin13                                          (Port_PinType)190
#define PortConf_PortGroup25_PortPin14                                          (Port_PinType)191
#define PortConf_PortGroup25_PortPin15                                          (Port_PinType)192
#define PortConf_PortGroup26_PortPin0                                           (Port_PinType)193
#define PortConf_PortGroup27_PortPin0                                           (Port_PinType)194
#define PortConf_PortGroup28_PortPin1                                           (Port_PinType)195
#define PortConf_PortGroup30_PortPin0                                           (Port_PinType)196
#define PortConf_PortGroup30_PortPin1                                           (Port_PinType)197
#define PortConf_PortGroup30_PortPin2                                           (Port_PinType)198
#define PortConf_PortGroup30_PortPin3                                           (Port_PinType)199
#define PortConf_PortGroup30_PortPin4                                           (Port_PinType)200
#define PortConf_PortGroup30_PortPin5                                           (Port_PinType)201
#define PortConf_PortGroup30_PortPin6                                           (Port_PinType)202
#define PortConf_PortGroup30_PortPin7                                           (Port_PinType)203
#define PortConf_PortGroup30_PortPin8                                           (Port_PinType)204
#define PortConf_PortGroup30_PortPin9                                           (Port_PinType)205
#define PortConf_PortGroup30_PortPin10                                          (Port_PinType)206
#define PortConf_PortGroup30_PortPin11                                          (Port_PinType)207
#define PortConf_PortGroup30_PortPin12                                          (Port_PinType)208
#define PortConf_PortGroup30_PortPin13                                          (Port_PinType)209
#define PortConf_PortGroup30_PortPin14                                          (Port_PinType)210
#define PortConf_PortGroup30_PortPin15                                          (Port_PinType)211
#define PortConf_PortGroup31_PortPin0                                           (Port_PinType)212
#define PortConf_PortGroup31_PortPin1                                           (Port_PinType)213
#define PortConf_PortGroup31_PortPin2                                           (Port_PinType)214
#define PortConf_PortGroup31_PortPin3                                           (Port_PinType)215
#define PortConf_PortGroup31_PortPin4                                           (Port_PinType)216
#define PortConf_PortGroup31_PortPin5                                           (Port_PinType)217
#define PortConf_PortGroup31_PortPin6                                           (Port_PinType)218
#define PortConf_PortGroup31_PortPin7                                           (Port_PinType)219
#define PortConf_PortGroup31_PortPin8                                           (Port_PinType)220
#define PortConf_PortGroup31_PortPin9                                           (Port_PinType)221
#define PortConf_PortGroup31_PortPin10                                          (Port_PinType)222
#define PortConf_PortGroup31_PortPin11                                          (Port_PinType)223
#define PortConf_PortGroup31_PortPin12                                          (Port_PinType)224
#define PortConf_PortGroup31_PortPin13                                          (Port_PinType)225
#define PortConf_PortGroup31_PortPin14                                          (Port_PinType)226
#define PortConf_PortGroup31_PortPin15                                          (Port_PinType)227
#define PortConf_PortGroup32_PortPin2                                           (Port_PinType)228
#define PortConf_PortGroup32_PortPin3                                           (Port_PinType)229
#define PortConf_PortGroup32_PortPin5                                           (Port_PinType)230
#define PortConf_PortGroup32_PortPin6                                           (Port_PinType)231
#define PortConf_PortGroup32_PortPin7                                           (Port_PinType)232
#define PortConf_PortGroup33_PortPin0                                           (Port_PinType)233
#define PortConf_PortGroup33_PortPin1                                           (Port_PinType)234
#define PortConf_PortGroup33_PortPin2                                           (Port_PinType)235
#define PortConf_PortGroup33_PortPin3                                           (Port_PinType)236
#define PortConf_PortGroup33_PortPin4                                           (Port_PinType)237
#define PortConf_PortGroup33_PortPin5                                           (Port_PinType)238
#define PortConf_PortGroup33_PortPin6                                           (Port_PinType)239
#define PortConf_PortGroup33_PortPin7                                           (Port_PinType)240
#define PortConf_PortGroup33_PortPin8                                           (Port_PinType)241
#define PortConf_PortGroup33_PortPin9                                           (Port_PinType)242
#define PortConf_PortGroup33_PortPin10                                          (Port_PinType)243
#define PortConf_PortGroup33_PortPin11                                          (Port_PinType)244
#define PortConf_PortGroup33_PortPin12                                          (Port_PinType)245
#define PortConf_PortGroup33_PortPin13                                          (Port_PinType)246
#define PortConf_PortGroup33_PortPin14                                          (Port_PinType)247
#define PortConf_PortGroup33_PortPin15                                          (Port_PinType)248
#define PortConf_PortGroup34_PortPin1                                           (Port_PinType)249
#define PortConf_PortGroup34_PortPin2                                           (Port_PinType)250
#define PortConf_PortGroup34_PortPin3                                           (Port_PinType)251
#define PortConf_PortGroup34_PortPin4                                           (Port_PinType)252
#define PortConf_PortGroup34_PortPin5                                           (Port_PinType)253
#define PortConf_PortGroup34_PortPin13                                          (Port_PinType)254
#define PortConf_PortGroup34_PortPin14                                          (Port_PinType)255
#define PortConf_PortGroup36_PortPin0                                           (Port_PinType)256
#define PortConf_PortGroup36_PortPin1                                           (Port_PinType)257
#define PortConf_PortGroup36_PortPin2                                           (Port_PinType)258
#define PortConf_PortGroup36_PortPin3                                           (Port_PinType)259
#define PortConf_PortGroup36_PortPin4                                           (Port_PinType)260
#define PortConf_PortGroup36_PortPin5                                           (Port_PinType)261
#define PortConf_PortGroup36_PortPin6                                           (Port_PinType)262
#define PortConf_PortGroup36_PortPin7                                           (Port_PinType)263
#define PortConf_PortGroup36_PortPin8                                           (Port_PinType)264
#define PortConf_PortGroup36_PortPin9                                           (Port_PinType)265
#define PortConf_PortGroup36_PortPin10                                          (Port_PinType)266
#define PortConf_PortGroup36_PortPin11                                          (Port_PinType)267
#define PortConf_PortGroup36_PortPin12                                          (Port_PinType)268
#define PortConf_PortGroup36_PortPin13                                          (Port_PinType)269
#define PortConf_PortGroup36_PortPin14                                          (Port_PinType)270
#define PortConf_PortGroup36_PortPin15                                          (Port_PinType)271
#define PortConf_PortGroup37_PortPin0                                           (Port_PinType)272
#define PortConf_PortGroup37_PortPin1                                           (Port_PinType)273
#define PortConf_PortGroup37_PortPin2                                           (Port_PinType)274
#define PortConf_PortGroup37_PortPin3                                           (Port_PinType)275
#define PortConf_PortGroup37_PortPin4                                           (Port_PinType)276
#define PortConf_PortGroup37_PortPin5                                           (Port_PinType)277
#define PortConf_PortGroup37_PortPin6                                           (Port_PinType)278
#define PortConf_PortGroup37_PortPin7                                           (Port_PinType)279
#define PortConf_PortGroup37_PortPin8                                           (Port_PinType)280
#define PortConf_PortGroup37_PortPin9                                           (Port_PinType)281
#define PortConf_PortGroup37_PortPin10                                          (Port_PinType)282
#define PortConf_PortGroup37_PortPin11                                          (Port_PinType)283
#define PortConf_PortGroup37_PortPin12                                          (Port_PinType)284
#define PortConf_PortGroup37_PortPin13                                          (Port_PinType)285
#define PortConf_PortGroup37_PortPin14                                          (Port_PinType)286
#define PortConf_PortGroup37_PortPin15                                          (Port_PinType)287
#define PortConf_PortGroup38_PortPin0                                           (Port_PinType)288
#define PortConf_PortGroup38_PortPin1                                           (Port_PinType)289
#define PortConf_PortGroup38_PortPin2                                           (Port_PinType)290
#define PortConf_PortGroup38_PortPin3                                           (Port_PinType)291
#define PortConf_PortGroup38_PortPin4                                           (Port_PinType)292
#define PortConf_PortGroup38_PortPin5                                           (Port_PinType)293
#define PortConf_PortGroup38_PortPin6                                           (Port_PinType)294
#define PortConf_PortGroup38_PortPin7                                           (Port_PinType)295
#define PortConf_PortGroup38_PortPin8                                           (Port_PinType)296
#define PortConf_PortGroup38_PortPin9                                           (Port_PinType)297
#define PortConf_PortGroup38_PortPin10                                          (Port_PinType)298
#define PortConf_PortGroup38_PortPin11                                          (Port_PinType)299
#define PortConf_PortGroup38_PortPin12                                          (Port_PinType)300
#define PortConf_PortGroup38_PortPin13                                          (Port_PinType)301
#define PortConf_PortGroup38_PortPin14                                          (Port_PinType)302
#define PortConf_PortGroup38_PortPin15                                          (Port_PinType)303
#define PortConf_PortGroup39_PortPin0                                           (Port_PinType)304
#define PortConf_PortGroup39_PortPin1                                           (Port_PinType)305
#define PortConf_PortGroup39_PortPin2                                           (Port_PinType)306
#define PortConf_PortGroup39_PortPin3                                           (Port_PinType)307
#define PortConf_PortGroup39_PortPin4                                           (Port_PinType)308
#define PortConf_PortGroup39_PortPin5                                           (Port_PinType)309
#define PortConf_PortGroup39_PortPin6                                           (Port_PinType)310
#define PortConf_PortGroup39_PortPin7                                           (Port_PinType)311
#define PortConf_PortGroup39_PortPin8                                           (Port_PinType)312
#define PortConf_PortGroup39_PortPin9                                           (Port_PinType)313
#define PortConf_PortGroup39_PortPin10                                          (Port_PinType)314
#define PortConf_PortGroup39_PortPin11                                          (Port_PinType)315
#define PortConf_PortGroup39_PortPin12                                          (Port_PinType)316
#define PortConf_PortGroup39_PortPin13                                          (Port_PinType)317
#define PortConf_PortGroup39_PortPin14                                          (Port_PinType)318
#define PortConf_PortGroup39_PortPin15                                          (Port_PinType)319
#define PortConf_PortGroup40_PortPin0                                           (Port_PinType)320
#define PortConf_PortGroup40_PortPin1                                           (Port_PinType)321
#define PortConf_PortGroup40_PortPin2                                           (Port_PinType)322
#define PortConf_PortGroup40_PortPin3                                           (Port_PinType)323
#define PortConf_PortGroup40_PortPin4                                           (Port_PinType)324
#define PortConf_PortGroup40_PortPin5                                           (Port_PinType)325
#define PortConf_PortGroup40_PortPin6                                           (Port_PinType)326
#define PortConf_PortGroup40_PortPin7                                           (Port_PinType)327
#define PortConf_PortGroup40_PortPin8                                           (Port_PinType)328
#define PortConf_PortGroup40_PortPin9                                           (Port_PinType)329
#define PortConf_PortGroup40_PortPin11                                          (Port_PinType)330
#define PortConf_PortGroup40_PortPin12                                          (Port_PinType)331
#define PortConf_PortGroup40_PortPin13                                          (Port_PinType)332
#define PortConf_PortGroup40_PortPin14                                          (Port_PinType)333
#define PortConf_PortGroup40_PortPin15                                          (Port_PinType)334
#define PortConf_PortGroup41_PortPin0                                           (Port_PinType)335
#define PortConf_PortGroup41_PortPin1                                           (Port_PinType)336
#define PortConf_PortGroup41_PortPin2                                           (Port_PinType)337
#define PortConf_PortGroup41_PortPin3                                           (Port_PinType)338
#define PortConf_PortGroup41_PortPin4                                           (Port_PinType)339
#define PortConf_PortGroup41_PortPin5                                           (Port_PinType)340
#define PortConf_PortGroup41_PortPin6                                           (Port_PinType)341
#define PortConf_PortGroup41_PortPin7                                           (Port_PinType)342
#define PortConf_PortGroup41_PortPin8                                           (Port_PinType)343
#define PortConf_PortGroup41_PortPin9                                           (Port_PinType)344
#define PortConf_PortGroup41_PortPin10                                          (Port_PinType)345
#define PortConf_PortGroup41_PortPin11                                          (Port_PinType)346
#define PortConf_PortGroup41_PortPin12                                          (Port_PinType)347
#define PortConf_PortGroup41_PortPin13                                          (Port_PinType)348
#define PortConf_PortGroup41_PortPin14                                          (Port_PinType)349
#define PortConf_PortGroup41_PortPin15                                          (Port_PinType)350
#define PortConf_PortGroup42_PortPin0                                           (Port_PinType)351
#define PortConf_PortGroup42_PortPin1                                           (Port_PinType)352
#define PortConf_PortGroup42_PortPin2                                           (Port_PinType)353
#define PortConf_PortGroup42_PortPin3                                           (Port_PinType)354
#define PortConf_PortGroup42_PortPin4                                           (Port_PinType)355
#define PortConf_PortGroup42_PortPin5                                           (Port_PinType)356
#define PortConf_PortGroup42_PortPin6                                           (Port_PinType)357
#define PortConf_PortGroup42_PortPin7                                           (Port_PinType)358
#define PortConf_PortGroup42_PortPin8                                           (Port_PinType)359
#define PortConf_PortGroup42_PortPin9                                           (Port_PinType)360
#define PortConf_PortGroup42_PortPin10                                          (Port_PinType)361
#define PortConf_PortGroup42_PortPin11                                          (Port_PinType)362
#define PortConf_PortGroup42_PortPin12                                          (Port_PinType)363
#define PortConf_PortGroup42_PortPin13                                          (Port_PinType)364
#define PortConf_PortGroup42_PortPin14                                          (Port_PinType)365
#define PortConf_PortGroup42_PortPin15                                          (Port_PinType)366
#define PortConf_PortGroup43_PortPin0                                           (Port_PinType)367
#define PortConf_PortGroup43_PortPin1                                           (Port_PinType)368
#define PortConf_PortGroup43_PortPin2                                           (Port_PinType)369
#define PortConf_PortGroup43_PortPin3                                           (Port_PinType)370
#define PortConf_PortGroup43_PortPin4                                           (Port_PinType)371
#define PortConf_PortGroup43_PortPin5                                           (Port_PinType)372
#define PortConf_PortGroup43_PortPin6                                           (Port_PinType)373
#define PortConf_PortGroup43_PortPin7                                           (Port_PinType)374
#define PortConf_PortGroup43_PortPin8                                           (Port_PinType)375
#define PortConf_PortGroup43_PortPin9                                           (Port_PinType)376
#define PortConf_PortGroup43_PortPin10                                          (Port_PinType)377
#define PortConf_PortGroup43_PortPin11                                          (Port_PinType)378
#define PortConf_PortGroup43_PortPin12                                          (Port_PinType)379
#define PortConf_PortGroup43_PortPin13                                          (Port_PinType)380
#define PortConf_PortGroup43_PortPin14                                          (Port_PinType)381
#define PortConf_PortGroup43_PortPin15                                          (Port_PinType)382
#define PortConf_PortGroup44_PortPin0                                           (Port_PinType)383
#define PortConf_PortGroup44_PortPin1                                           (Port_PinType)384
#define PortConf_PortGroup44_PortPin2                                           (Port_PinType)385
#define PortConf_PortGroup44_PortPin3                                           (Port_PinType)386
#define PortConf_PortGroup44_PortPin4                                           (Port_PinType)387
#define PortConf_PortGroup44_PortPin5                                           (Port_PinType)388
#define PortConf_PortGroup44_PortPin6                                           (Port_PinType)389
#define PortConf_PortGroup44_PortPin7                                           (Port_PinType)390
#define PortConf_PortGroup44_PortPin8                                           (Port_PinType)391
#define PortConf_PortGroup44_PortPin9                                           (Port_PinType)392
#define PortConf_PortGroup44_PortPin10                                          (Port_PinType)393
#define PortConf_PortGroup44_PortPin11                                          (Port_PinType)394
#define PortConf_PortGroup44_PortPin12                                          (Port_PinType)395
#define PortConf_PortGroup44_PortPin13                                          (Port_PinType)396
#define PortConf_PortGroup44_PortPin14                                          (Port_PinType)397
#define PortConf_PortGroup44_PortPin15                                          (Port_PinType)398
#define PortConf_PortGroup45_PortPin0                                           (Port_PinType)399
#define PortConf_PortGroup45_PortPin1                                           (Port_PinType)400
#define PortConf_PortGroup45_PortPin2                                           (Port_PinType)401
#define PortConf_PortGroup45_PortPin3                                           (Port_PinType)402
#define PortConf_PortGroup45_PortPin4                                           (Port_PinType)403
#define PortConf_PortGroup45_PortPin5                                           (Port_PinType)404
#define PortConf_PortGroup45_PortPin6                                           (Port_PinType)405
#define PortConf_PortGroup45_PortPin7                                           (Port_PinType)406
#define PortConf_PortGroup45_PortPin8                                           (Port_PinType)407
#define PortConf_PortGroup45_PortPin9                                           (Port_PinType)408
#define PortConf_PortGroup45_PortPin10                                          (Port_PinType)409
#define PortConf_PortGroup45_PortPin11                                          (Port_PinType)410
#define PortConf_PortGroup45_PortPin12                                          (Port_PinType)411
#define PortConf_PortGroup45_PortPin13                                          (Port_PinType)412
#define PortConf_PortGroup45_PortPin14                                          (Port_PinType)413
#define PortConf_PortGroup45_PortPin15                                          (Port_PinType)414
#define PortConf_PortGroup46_PortPin0                                           (Port_PinType)415
#define PortConf_PortGroup46_PortPin1                                           (Port_PinType)416
#define PortConf_PortGroup46_PortPin2                                           (Port_PinType)417
#define PortConf_PortGroup46_PortPin3                                           (Port_PinType)418
#define PortConf_PortGroup46_PortPin4                                           (Port_PinType)419
#define PortConf_PortGroup46_PortPin5                                           (Port_PinType)420
#define PortConf_PortGroup46_PortPin6                                           (Port_PinType)421
#define PortConf_PortGroup46_PortPin7                                           (Port_PinType)422
#define PortConf_PortGroup46_PortPin8                                           (Port_PinType)423
#define PortConf_PortGroup46_PortPin9                                           (Port_PinType)424
#define PortConf_PortGroup46_PortPin10                                          (Port_PinType)425
#define PortConf_PortGroup46_PortPin11                                          (Port_PinType)426
#define PortConf_PortGroup46_PortPin12                                          (Port_PinType)427
#define PortConf_PortGroup46_PortPin13                                          (Port_PinType)428
#define PortConf_PortGroup46_PortPin14                                          (Port_PinType)429
#define PortConf_PortGroup46_PortPin15                                          (Port_PinType)430
#define PortConf_PortGroup47_PortPin0                                           (Port_PinType)431
#define PortConf_PortGroup47_PortPin1                                           (Port_PinType)432
#define PortConf_PortGroup47_PortPin2                                           (Port_PinType)433
#define PortConf_PortGroup47_PortPin3                                           (Port_PinType)434
#define PortConf_PortGroup47_PortPin4                                           (Port_PinType)435
#define PortConf_PortGroup47_PortPin5                                           (Port_PinType)436
#define PortConf_PortGroup47_PortPin6                                           (Port_PinType)437
#define PortConf_PortGroup47_PortPin7                                           (Port_PinType)438
#define PortConf_PortGroup47_PortPin8                                           (Port_PinType)439
#define PortConf_PortGroup47_PortPin9                                           (Port_PinType)440
#define PortConf_PortGroup47_PortPin10                                          (Port_PinType)441
#define PortConf_PortGroup47_PortPin11                                          (Port_PinType)442
#define PortConf_PortGroup47_PortPin12                                          (Port_PinType)443
#define PortConf_PortGroup47_PortPin13                                          (Port_PinType)444
#define PortConf_PortGroup47_PortPin14                                          (Port_PinType)445
#define PortConf_PortGroup47_PortPin15                                          (Port_PinType)446
#define PortConf_PortGroup48_PortPin0                                           (Port_PinType)447
#define PortConf_PortGroup48_PortPin1                                           (Port_PinType)448
#define PortConf_PortGroup48_PortPin2                                           (Port_PinType)449
#define PortConf_PortGroup48_PortPin3                                           (Port_PinType)450
#define PortConf_PortGroup48_PortPin4                                           (Port_PinType)451
#define PortConf_PortGroup48_PortPin5                                           (Port_PinType)452
#define PortConf_PortGroup48_PortPin6                                           (Port_PinType)453
#define PortConf_PortGroup48_PortPin7                                           (Port_PinType)454
#define PortConf_PortGroup48_PortPin8                                           (Port_PinType)455
#define PortConf_PortGroup48_PortPin9                                           (Port_PinType)456
#define PortConf_PortGroup48_PortPin10                                          (Port_PinType)457
#define PortConf_PortGroup48_PortPin11                                          (Port_PinType)458
#define PortConf_PortGroup48_PortPin12                                          (Port_PinType)459
#define PortConf_PortGroup48_PortPin13                                          (Port_PinType)460
#define PortConf_PortGroup48_PortPin14                                          (Port_PinType)461
#define PortConf_PortGroup48_PortPin15                                          (Port_PinType)462
#define PortConf_PortGroup49_PortPin0                                           (Port_PinType)463
#define PortConf_PortGroup49_PortPin1                                           (Port_PinType)464
#define PortConf_PortGroup49_PortPin2                                           (Port_PinType)465
#define PortConf_PortGroup49_PortPin3                                           (Port_PinType)466
#define PortConf_PortGroup49_PortPin4                                           (Port_PinType)467
#define PortConf_PortGroup49_PortPin5                                           (Port_PinType)468
#define PortConf_PortGroup49_PortPin6                                           (Port_PinType)469
#define PortConf_PortGroup49_PortPin7                                           (Port_PinType)470
#define PortConf_PortGroup49_PortPin8                                           (Port_PinType)471
#define PortConf_PortGroup49_PortPin9                                           (Port_PinType)472
#define PortConf_PortGroup49_PortPin10                                          (Port_PinType)473
#define PortConf_PortGroup49_PortPin11                                          (Port_PinType)474
#define PortConf_PortGroup49_PortPin12                                          (Port_PinType)475
#define PortConf_PortGroup49_PortPin13                                          (Port_PinType)476
#define PortConf_PortGroup49_PortPin14                                          (Port_PinType)477
#define PortConf_PortGroup49_PortPin15                                          (Port_PinType)478
#define PortConf_PortGroup50_PortPin0                                           (Port_PinType)479
#define PortConf_PortGroup50_PortPin1                                           (Port_PinType)480
#define PortConf_PortGroup50_PortPin2                                           (Port_PinType)481
#define PortConf_PortGroup50_PortPin3                                           (Port_PinType)482
#define PortConf_PortGroup50_PortPin4                                           (Port_PinType)483
#define PortConf_PortGroup50_PortPin5                                           (Port_PinType)484
#define PortConf_PortGroup50_PortPin6                                           (Port_PinType)485
#define PortConf_PortGroup50_PortPin7                                           (Port_PinType)486
#define PortConf_PortGroup50_PortPin8                                           (Port_PinType)487
#define PortConf_PortGroup50_PortPin9                                           (Port_PinType)488
#define PortConf_PortGroup50_PortPin10                                          (Port_PinType)489
#define PortConf_PortGroup50_PortPin11                                          (Port_PinType)490
#define PortConf_PortGroup50_PortPin12                                          (Port_PinType)491
#define PortConf_PortGroup50_PortPin13                                          (Port_PinType)492
#define PortConf_PortGroup50_PortPin14                                          (Port_PinType)493
#define PortConf_PortGroup50_PortPin15                                          (Port_PinType)494
#define PortConf_PortGroup51_PortPin0                                           (Port_PinType)495
#define PortConf_PortGroup51_PortPin1                                           (Port_PinType)496
#define PortConf_PortGroup51_PortPin2                                           (Port_PinType)497
#define PortConf_PortGroup51_PortPin3                                           (Port_PinType)498
#define PortConf_PortGroup51_PortPin4                                           (Port_PinType)499
#define PortConf_PortGroup51_PortPin5                                           (Port_PinType)500
#define PortConf_PortGroup51_PortPin6                                           (Port_PinType)501
#define PortConf_PortGroup51_PortPin7                                           (Port_PinType)502
#define PortConf_PortGroup51_PortPin8                                           (Port_PinType)503
#define PortConf_PortGroup51_PortPin9                                           (Port_PinType)504
#define PortConf_PortGroup51_PortPin10                                          (Port_PinType)505
#define PortConf_PortGroup51_PortPin11                                          (Port_PinType)506
#define PortConf_PortGroup51_PortPin12                                          (Port_PinType)507
#define PortConf_PortGroup51_PortPin13                                          (Port_PinType)508
#define PortConf_PortGroup51_PortPin14                                          (Port_PinType)509
#define PortConf_PortGroup51_PortPin15                                          (Port_PinType)510
#define PortConf_PortGroup52_PortPin0                                           (Port_PinType)511
#define PortConf_PortGroup52_PortPin1                                           (Port_PinType)512
#define PortConf_PortGroup52_PortPin2                                           (Port_PinType)513
#define PortConf_PortGroup52_PortPin3                                           (Port_PinType)514
#define PortConf_PortGroup52_PortPin4                                           (Port_PinType)515
#define PortConf_PortGroup52_PortPin5                                           (Port_PinType)516
#define PortConf_PortGroup52_PortPin6                                           (Port_PinType)517
#define PortConf_PortGroup52_PortPin7                                           (Port_PinType)518
#define PortConf_PortGroup52_PortPin8                                           (Port_PinType)519
#define PortConf_PortGroup52_PortPin9                                           (Port_PinType)520
#define PortConf_PortGroup52_PortPin10                                          (Port_PinType)521
#define PortConf_PortGroup52_PortPin11                                          (Port_PinType)522
#define PortConf_PortGroup52_PortPin12                                          (Port_PinType)523
#define PortConf_PortGroup52_PortPin13                                          (Port_PinType)524
#define PortConf_PortGroup52_PortPin14                                          (Port_PinType)525
#define PortConf_PortGroup52_PortPin15                                          (Port_PinType)526
#define PortConf_PortGroup53_PortPin0                                           (Port_PinType)527
#define PortConf_PortGroup53_PortPin1                                           (Port_PinType)528
#define PortConf_PortGroup53_PortPin2                                           (Port_PinType)529
#define PortConf_PortGroup53_PortPin3                                           (Port_PinType)530
#define PortConf_PortGroup53_PortPin4                                           (Port_PinType)531
#define PortConf_PortGroup53_PortPin5                                           (Port_PinType)532
#define PortConf_PortGroup53_PortPin6                                           (Port_PinType)533
#define PortConf_PortGroup53_PortPin7                                           (Port_PinType)534
#define PortConf_PortGroup53_PortPin8                                           (Port_PinType)535
#define PortConf_PortGroup53_PortPin9                                           (Port_PinType)536
#define PortConf_PortGroup53_PortPin10                                          (Port_PinType)537
#define PortConf_PortGroup53_PortPin11                                          (Port_PinType)538
#define PortConf_PortGroup53_PortPin12                                          (Port_PinType)539
#define PortConf_PortGroup53_PortPin13                                          (Port_PinType)540
#define PortConf_PortGroup53_PortPin14                                          (Port_PinType)541
#define PortConf_PortGroup53_PortPin15                                          (Port_PinType)542
#define PortConf_PortGroup54_PortPin0                                           (Port_PinType)543
#define PortConf_PortGroup54_PortPin1                                           (Port_PinType)544
#define PortConf_PortGroup54_PortPin2                                           (Port_PinType)545
#define PortConf_PortGroup54_PortPin3                                           (Port_PinType)546
#define PortConf_PortGroup54_PortPin4                                           (Port_PinType)547
#define PortConf_PortGroup54_PortPin5                                           (Port_PinType)548
#define PortConf_PortGroup54_PortPin6                                           (Port_PinType)549
#define PortConf_PortGroup54_PortPin7                                           (Port_PinType)550
#define PortConf_PortGroup54_PortPin8                                           (Port_PinType)551
#define PortConf_PortGroup54_PortPin9                                           (Port_PinType)552
#define PortConf_PortGroup54_PortPin10                                          (Port_PinType)553
#define PortConf_PortGroup54_PortPin11                                          (Port_PinType)554
#define PortConf_PortGroup54_PortPin12                                          (Port_PinType)555
#define PortConf_PortGroup54_PortPin13                                          (Port_PinType)556
#define PortConf_PortGroup54_PortPin14                                          (Port_PinType)557
#define PortConf_PortGroup54_PortPin15                                          (Port_PinType)558
#define PortConf_PortGroup55_PortPin0                                           (Port_PinType)559
#define PortConf_PortGroup55_PortPin1                                           (Port_PinType)560
#define PortConf_PortGroup55_PortPin2                                           (Port_PinType)561
#define PortConf_PortGroup55_PortPin3                                           (Port_PinType)562
#define PortConf_PortGroup55_PortPin4                                           (Port_PinType)563
#define PortConf_PortGroup55_PortPin5                                           (Port_PinType)564
#define PortConf_PortGroup55_PortPin6                                           (Port_PinType)565
#define PortConf_PortGroup55_PortPin7                                           (Port_PinType)566
#define PortConf_PortGroup55_PortPin8                                           (Port_PinType)567
#define PortConf_PortGroup55_PortPin9                                           (Port_PinType)568
#define PortConf_PortGroup55_PortPin10                                          (Port_PinType)569
#define PortConf_PortGroup55_PortPin11                                          (Port_PinType)570
#define PortConf_PortGroup55_PortPin12                                          (Port_PinType)571
#define PortConf_PortGroup55_PortPin13                                          (Port_PinType)572
#define PortConf_PortGroup55_PortPin14                                          (Port_PinType)573
#define PortConf_PortGroup55_PortPin15                                          (Port_PinType)574
#define PortConf_PortGroup56_PortPin0                                           (Port_PinType)575
#define PortConf_PortGroup56_PortPin1                                           (Port_PinType)576
#define PortConf_PortGroup56_PortPin2                                           (Port_PinType)577
#define PortConf_PortGroup56_PortPin3                                           (Port_PinType)578
#define PortConf_PortGroup56_PortPin4                                           (Port_PinType)579
#define PortConf_PortGroup56_PortPin5                                           (Port_PinType)580
#define PortConf_PortGroup56_PortPin6                                           (Port_PinType)581
#define PortConf_PortGroup56_PortPin7                                           (Port_PinType)582
#define PortConf_PortGroup56_PortPin8                                           (Port_PinType)583
#define PortConf_PortGroup56_PortPin9                                           (Port_PinType)584
#define PortConf_PortGroup56_PortPin10                                          (Port_PinType)585
#define PortConf_PortGroup56_PortPin11                                          (Port_PinType)586
#define PortConf_PortGroup56_PortPin12                                          (Port_PinType)587
#define PortConf_PortGroup56_PortPin13                                          (Port_PinType)588
#define PortConf_PortGroup56_PortPin14                                          (Port_PinType)589
#define PortConf_PortGroup56_PortPin15                                          (Port_PinType)590
#define PortConf_PortGroup57_PortPin0                                           (Port_PinType)591
#define PortConf_PortGroup57_PortPin1                                           (Port_PinType)592
#define PortConf_PortGroup57_PortPin2                                           (Port_PinType)593
#define PortConf_PortGroup57_PortPin3                                           (Port_PinType)594
#define PortConf_PortGroup57_PortPin4                                           (Port_PinType)595
#define PortConf_PortGroup57_PortPin5                                           (Port_PinType)596
#define PortConf_PortGroup57_PortPin6                                           (Port_PinType)597
#define PortConf_PortGroup57_PortPin7                                           (Port_PinType)598
#define PortConf_PortGroup57_PortPin8                                           (Port_PinType)599
#define PortConf_PortGroup57_PortPin9                                           (Port_PinType)600
#define PortConf_PortGroup57_PortPin10                                          (Port_PinType)601
#define PortConf_PortGroup57_PortPin11                                          (Port_PinType)602
#define PortConf_PortGroup57_PortPin12                                          (Port_PinType)603
#define PortConf_PortGroup57_PortPin13                                          (Port_PinType)604
#define PortConf_PortGroup57_PortPin14                                          (Port_PinType)605
#define PortConf_PortGroup57_PortPin15                                          (Port_PinType)606
#define PortConf_PortGroup58_PortPin0                                           (Port_PinType)607
#define PortConf_PortGroup58_PortPin1                                           (Port_PinType)608
#define PortConf_PortGroup58_PortPin2                                           (Port_PinType)609
#define PortConf_PortGroup58_PortPin3                                           (Port_PinType)610
#define PortConf_PortGroup58_PortPin4                                           (Port_PinType)611
#define PortConf_PortGroup58_PortPin5                                           (Port_PinType)612
#define PortConf_PortGroup58_PortPin6                                           (Port_PinType)613
#define PortConf_PortGroup58_PortPin7                                           (Port_PinType)614
#define PortConf_PortGroup58_PortPin8                                           (Port_PinType)615
#define PortConf_PortGroup58_PortPin9                                           (Port_PinType)616
#define PortConf_PortGroup58_PortPin10                                          (Port_PinType)617
#define PortConf_PortGroup58_PortPin11                                          (Port_PinType)618
#define PortConf_PortGroup58_PortPin12                                          (Port_PinType)619
#define PortConf_PortGroup58_PortPin13                                          (Port_PinType)620
#define PortConf_PortGroup58_PortPin14                                          (Port_PinType)621
#define PortConf_PortGroup58_PortPin15                                          (Port_PinType)622
#define PortConf_PortGroup59_PortPin0                                           (Port_PinType)623
#define PortConf_PortGroup59_PortPin1                                           (Port_PinType)624
#define PortConf_PortGroup59_PortPin2                                           (Port_PinType)625
#define PortConf_PortGroup59_PortPin3                                           (Port_PinType)626
#define PortConf_PortGroup59_PortPin4                                           (Port_PinType)627
#define PortConf_PortGroup59_PortPin5                                           (Port_PinType)628
#define PortConf_PortGroup59_PortPin6                                           (Port_PinType)629
#define PortConf_PortGroup59_PortPin7                                           (Port_PinType)630
#define PortConf_PortGroup59_PortPin8                                           (Port_PinType)631
#define PortConf_PortGroup59_PortPin9                                           (Port_PinType)632
#define PortConf_PortGroup59_PortPin10                                          (Port_PinType)633
#define PortConf_PortGroup59_PortPin11                                          (Port_PinType)634
#define PortConf_PortGroup59_PortPin12                                          (Port_PinType)635
#define PortConf_PortGroup59_PortPin13                                          (Port_PinType)636
#define PortConf_PortGroup59_PortPin14                                          (Port_PinType)637
#define PortConf_PortGroup59_PortPin15                                          (Port_PinType)638
#define PortConf_PortGroup60_PortPin0                                           (Port_PinType)639
#define PortConf_PortGroup60_PortPin1                                           (Port_PinType)640
#define PortConf_PortGroup60_PortPin2                                           (Port_PinType)641
#define PortConf_PortGroup60_PortPin3                                           (Port_PinType)642
#define PortConf_PortGroup60_PortPin4                                           (Port_PinType)643
#define PortConf_PortGroup60_PortPin5                                           (Port_PinType)644
#define PortConf_PortGroup60_PortPin6                                           (Port_PinType)645
#define PortConf_PortGroup60_PortPin7                                           (Port_PinType)646
#define PortConf_PortGroup60_PortPin8                                           (Port_PinType)647
#define PortConf_PortGroup60_PortPin9                                           (Port_PinType)648
#define PortConf_PortGroup60_PortPin10                                          (Port_PinType)649
#define PortConf_PortGroup60_PortPin11                                          (Port_PinType)650
#define PortConf_PortGroup60_PortPin12                                          (Port_PinType)651
#define PortConf_PortGroup60_PortPin13                                          (Port_PinType)652
#define PortConf_PortGroup60_PortPin14                                          (Port_PinType)653
#define PortConf_PortGroup60_PortPin15                                          (Port_PinType)654
#define PortConf_PortGroupJtag0_PortPin0                                        (Port_PinType)655
#define PortConf_PortGroupJtag0_PortPin1                                        (Port_PinType)656
#define PortConf_PortGroupJtag0_PortPin2                                        (Port_PinType)657
#define PortConf_PortGroupJtag0_PortPin3                                        (Port_PinType)658
#define PortConf_PortGroupJtag0_PortPin5                                        (Port_PinType)659



/* Configuration Set Handles */
#define Port_Config                                                             (&Port_GaaConfiguration[0])

/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/



#endif /* PORT_CFG_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

