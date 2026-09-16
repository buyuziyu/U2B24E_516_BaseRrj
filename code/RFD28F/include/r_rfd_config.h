/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_config.h
    Program Version : V1.00
    File Revision   : $Rev: 2509 $
    File Date       : $Date:: 2021-09-17 10:42:06 +0900#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : For RH850/U2Bx
**********************************************************************************************************************/

#ifndef R_RFD_CONFIG_H
#define R_RFD_CONFIG_H

/**********************************************************************************************************************
    Include file that is defined constants
**********************************************************************************************************************/

#include "r_rfd_constant.h"

/**********************************************************************************************************************
    
    This is user configuration file
    
**********************************************************************************************************************/

/**********************************************************************************************************************
    Timeout count
    
    This is used by "R_RFD_ForcedStopAndErrorClear".
    This value is used for "loop count of for loop statement".
**********************************************************************************************************************/

#define R_RFD_VALUE_FORCED_STOP_TIMEOUT     300U

/**********************************************************************************************************************
    Selects erasure-suspended mode to be entered when the programming/erasure suspension command is issued while
    flash sequencer is erasing flash memory
    
    R_RFD_SUSPENSION_PRIORITY_MODE  : Suspension-priority mode
    R_RFD_ERASURE_PRIORITY_MODE     : Erasure-priority mode
**********************************************************************************************************************/

#define R_RFD_ERASURE_SUSPENDED_MODE    R_RFD_NO_DEFINITION

/**********************************************************************************************************************
    Flash Access Error Interrupt Enable/Disable
    
    This is the value for the FAEINT register
    
    R_RFD_REG_FAEINT_CFAEIE  : CFAEIE bit (Code Flash Access Error Interrupt Enable)
      - R_RFD_DISABLE : Does not generate the FLERR interrupt request when FASTAT_n.CFAE = 1
      - R_RFD_ENABLE  : Generates the FLERR interrupt request when FASTAT_n.CFAE = 1
    
    R_RFD_REG_FAEINT_CMDLKIE : CMDLKIE bit (Command Lock Interrupt Enable)
      - R_RFD_DISABLE : Does not generate the FLERR interrupt request when FASTAT_n.CMDLK = 1
      - R_RFD_ENABLE  : Generates the FLERR interrupt request when FASTAT_n.CMDLK = 1
    
    R_RFD_REG_FAEINT_DFAEIE  : DFAEIE bit (Data Flash Access Error Interrupt Enable)
      - R_RFD_DISABLE : Does not generate the FLERR interrupt request when FASTAT_n.DFAE = 1
      - R_RFD_ENABLE  : Generates the FLERR interrupt request when FASTAT_n.DFAE = 1
    
    R_RFD_REG_FAEINT_ECRCTIE : ECRCTIE bit (Error Correction Interrupt Enable)
      - R_RFD_DISABLE : Does not generate the FLERR interrupt request when FASTAT_n.ECRCT = 1
      - R_RFD_ENABLE  : Generates the FLERR interrupt request when FASTAT_n.ECRCT = 1
**********************************************************************************************************************/

#define R_RFD_REG_FAEINT_CFAEIE     R_RFD_DISABLE
#define R_RFD_REG_FAEINT_CMDLKIE    R_RFD_DISABLE
#define R_RFD_REG_FAEINT_DFAEIE     R_RFD_DISABLE
#define R_RFD_REG_FAEINT_ECRCTIE    R_RFD_DISABLE

/**********************************************************************************************************************
    Definition for each devices
    
    Set the pre-processor option for the device to be used as follows.
    (The following devices are defined in advance and are enabled by setting pre-processor option)
    
    - RH850/U2B6           : -D__RH850_U2B6__
    - RH850/U2B10          : -D__RH850_U2B10__
    
    If none of the above is defined, the definitions below #else are valid.
    It can be used for custom definition.
**********************************************************************************************************************/


#if   defined(__RH850_U2B6__)

/**********************************************************************************************************************
    Number of FACI
        - FACI0 only                : 1
        - FACI0 and FACI2           : 2
**********************************************************************************************************************/

#define R_RFD_NUMBER_OF_FACI        2

/**********************************************************************************************************************
    Base address of FACI
**********************************************************************************************************************/

#define R_RFD_BASE_ADDRESS_FACI0    0xFFA10000UL    /* FACI0 Base address */
#define R_RFD_BASE_ADDRESS_FACI2    0xFFA18000UL    /* FACI2 Base address */

/**********************************************************************************************************************
    Address of FACI command issue area
**********************************************************************************************************************/

#define R_RFD_CMDAREA_FACI0         0xFFA20000UL    /* FACI0 Command-issuing area */
#define R_RFD_CMDAREA_FACI2         0xFFA40000UL    /* FACI2 Command-issuing area */

/**********************************************************************************************************************
    Address of FHVE register
**********************************************************************************************************************/

#define R_RFD_REG_ADDRESS_FHVE3_0   0xFF984800UL    /* FHVE3FP0 register address (For FACI0)  */
#define R_RFD_REG_ADDRESS_FHVE15_0  0xFF984804UL    /* FHVE15FP0 register address (For FACI0) */

#define R_RFD_REG_ADDRESS_FHVE3_2   0xFF984820UL    /* FHVE3FP1 register address (For FACI2)  */
#define R_RFD_REG_ADDRESS_FHVE15_2  0xFF984824UL    /* FHVE15FP1 register address (For FACI2) */

/**********************************************************************************************************************
    For "Data flash" control setting
**********************************************************************************************************************/

/**********************************************************************************************************************
    Data Flash is controlled by RFD28F?
      - R_RFD_ENABLE  : Data Flash Memory is controlled by RFD28F
      - R_RFD_DISABLE : Data Flash Memory is not controlled by RFD28F
    
    If this definition is "R_RFD_DISABLE", APIs related Data Flash Memory are not executed.
**********************************************************************************************************************/

#define R_RFD_CONTROL_TARGET_DATAFLASH  R_RFD_ENABLE    /* Data Flash Memory is controlled by RFD28F or not */

/**********************************************************************************************************************
    Address of Data Flash area
**********************************************************************************************************************/

#define R_RFD_DF_BASE_FACI0         0xFF200000UL        /* Start address of Data Flash Memory (controlled by FACI0) */
#define R_RFD_DF_BASE_FACI1         R_RFD_NO_DEFINITION /* Start address of Data Flash Memory (controlled by FACI1) */
#define R_RFD_DF_BASE_FACI2         0xFF220000UL        /* Start address of Data Flash Memory (controlled by FACI2) */
#define R_RFD_DF_END                0xFF22FFFFUL        /* End address of Data Flash Memory                         */

/**********************************************************************************************************************
    For "Code flash" control setting
**********************************************************************************************************************/

/**********************************************************************************************************************
    Code Flash is controlled by RFD28F?
      - R_RFD_ENABLE  : Code Flash Memory is controlled by RFD28F
      - R_RFD_DISABLE : Code Flash Memory is not controlled by RFD28F
    
    If this definition is "R_RFD_DISABLE", APIs related Code Flash Memory are not executed.
**********************************************************************************************************************/

#define R_RFD_CONTROL_TARGET_CODEFLASH  R_RFD_ENABLE    /* Code Flash Memory is controlled by RFD28F or not */

/**********************************************************************************************************************
    MAP Mode
        - Single map mode : R_RFD_SINGLE
        - Double map mode : R_RFD_DOUBLE
**********************************************************************************************************************/

#define R_RFD_MAPMODE                   R_RFD_SINGLE    /* MAP mode */

/**********************************************************************************************************************
    Block Protection area1 is exist?
        - Exist     : R_RFD_ENABLE
        - Not exist : R_RFD_DISABLE
**********************************************************************************************************************/

#define R_RFD_BLOCK_PROTECTION_AREA1    R_RFD_DISABLE   /* Block Protection area1 is exist? */

/**********************************************************************************************************************
    FPMON check is enable?
        - Enable    : R_RFD_ENABLE
        - Disable   : R_RFD_DISABLE
**********************************************************************************************************************/

#define R_RFD_FPMON_CHECK               R_RFD_ENABLE    /* FPMON register check is valid or invalid */

/**********************************************************************************************************************
    Address of Code Flash area
**********************************************************************************************************************/

#define R_RFD_CF_BASE_FACI0         0x00000000UL        /* Start address of Code Flash Memory (controlled by FACI0) */
#define R_RFD_CF_BASE_FACI1         R_RFD_NO_DEFINITION /* Start address of Code Flash Memory (controlled by FACI1) */
#define R_RFD_CF_BASE_FACI2         R_RFD_NO_DEFINITION /* Start address of Code Flash Memory (controlled by FACI2) */
#define R_RFD_CF_END                0x005FFFFFUL        /* End address of Code Flash Memory                         */

/**********************************************************************************************************************
    Address of Data Flash ECC Control Register (For Read access)
**********************************************************************************************************************/

#define R_RFD_BASE_ADDRESS_DFECC    0xFFC62C00UL        /* Address of Data Flash ECC Controller                     */




#elif   defined(__RH850_U2B10__)

/**********************************************************************************************************************
    Number of FACI
        - FACI0 only                : 1
        - FACI0 and FACI2           : 2
**********************************************************************************************************************/

#define R_RFD_NUMBER_OF_FACI        2

/**********************************************************************************************************************
    Base address of FACI
**********************************************************************************************************************/

#define R_RFD_BASE_ADDRESS_FACI0    0xFFA10000UL    /* FACI0 Base address */
#define R_RFD_BASE_ADDRESS_FACI2    0xFFA18000UL    /* FACI2 Base address */

/**********************************************************************************************************************
    Address of FACI command issue area
**********************************************************************************************************************/

#define R_RFD_CMDAREA_FACI0         0xFFA20000UL    /* FACI0 Command-issuing area */
#define R_RFD_CMDAREA_FACI2         0xFFA40000UL    /* FACI2 Command-issuing area */

/**********************************************************************************************************************
    Address of FHVE register
**********************************************************************************************************************/

#define R_RFD_REG_ADDRESS_FHVE3_0   0xFF984800UL    /* FHVE3FP0 register address (For FACI0)  */
#define R_RFD_REG_ADDRESS_FHVE15_0  0xFF984804UL    /* FHVE15FP0 register address (For FACI0) */

#define R_RFD_REG_ADDRESS_FHVE3_2   0xFF984820UL    /* FHVE3FP1 register address (For FACI2)  */
#define R_RFD_REG_ADDRESS_FHVE15_2  0xFF984824UL    /* FHVE15FP1 register address (For FACI2) */

/**********************************************************************************************************************
    For "Data flash" control setting
**********************************************************************************************************************/

/**********************************************************************************************************************
    Data Flash is controlled by RFD28F?
      - R_RFD_ENABLE  : Data Flash Memory is controlled by RFD28F
      - R_RFD_DISABLE : Data Flash Memory is not controlled by RFD28F
    
    If this definition is "R_RFD_DISABLE", APIs related Data Flash Memory are not executed.
**********************************************************************************************************************/

#define R_RFD_CONTROL_TARGET_DATAFLASH  R_RFD_ENABLE    /* Data Flash Memory is controlled by RFD28F or not */

/**********************************************************************************************************************
    Address of Data Flash area
**********************************************************************************************************************/

#define R_RFD_DF_BASE_FACI0         0xFF200000UL        /* Start address of Data Flash Memory (controlled by FACI0) */
#define R_RFD_DF_BASE_FACI1         R_RFD_NO_DEFINITION /* Start address of Data Flash Memory (controlled by FACI1) */
#define R_RFD_DF_BASE_FACI2         0xFF240000UL        /* Start address of Data Flash Memory (controlled by FACI2) */
#define R_RFD_DF_END                0xFF24FFFFUL        /* End address of Data Flash Memory                         */

/**********************************************************************************************************************
    For "Code flash" control setting
**********************************************************************************************************************/

/**********************************************************************************************************************
    Code Flash is controlled by RFD28F?
      - R_RFD_ENABLE  : Code Flash Memory is controlled by RFD28F
      - R_RFD_DISABLE : Code Flash Memory is not controlled by RFD28F
    
    If this definition is "R_RFD_DISABLE", APIs related Code Flash Memory are not executed.
**********************************************************************************************************************/

#define R_RFD_CONTROL_TARGET_CODEFLASH  R_RFD_ENABLE    /* Code Flash Memory is controlled by RFD28F or not */

/**********************************************************************************************************************
    MAP Mode
        - Single map mode : R_RFD_SINGLE
        - Double map mode : R_RFD_DOUBLE
**********************************************************************************************************************/

#define R_RFD_MAPMODE                   R_RFD_SINGLE    /* MAP mode */

/**********************************************************************************************************************
    Block Protection area1 is exist?
        - Exist     : R_RFD_ENABLE
        - Not exist : R_RFD_DISABLE
**********************************************************************************************************************/

#define R_RFD_BLOCK_PROTECTION_AREA1    R_RFD_DISABLE   /* Block Protection area1 is exist? */

/**********************************************************************************************************************
    FPMON check is enable?
        - Enable    : R_RFD_ENABLE
        - Disable   : R_RFD_DISABLE
**********************************************************************************************************************/

#define R_RFD_FPMON_CHECK               R_RFD_ENABLE    /* FPMON register check is valid or invalid */

/**********************************************************************************************************************
    Address of Code Flash area
**********************************************************************************************************************/

#define R_RFD_CF_BASE_FACI0         0x00000000UL        /* Start address of Code Flash Memory (controlled by FACI0) */
#define R_RFD_CF_BASE_FACI1         R_RFD_NO_DEFINITION /* Start address of Code Flash Memory (controlled by FACI1) */
#define R_RFD_CF_BASE_FACI2         R_RFD_NO_DEFINITION /* Start address of Code Flash Memory (controlled by FACI2) */
#define R_RFD_CF_END                0x009FFFFFUL        /* End address of Code Flash Memory                         */

/**********************************************************************************************************************
    Address of Data Flash ECC Control Register (For Read access)
**********************************************************************************************************************/

#define R_RFD_BASE_ADDRESS_DFECC    0xFFC62C00UL        /* Address of Data Flash ECC Controller                     */





/**********************************************************************************************************************
    
    For customize
    
**********************************************************************************************************************/

#else

/**********************************************************************************************************************
    Number of FACI
        - FACI0 only                : 1
        - FACI0 and FACI2           : 2
**********************************************************************************************************************/

#define R_RFD_NUMBER_OF_FACI        2

/**********************************************************************************************************************
    Base address of FACI
**********************************************************************************************************************/

#define R_RFD_BASE_ADDRESS_FACI0    0xFFA10000UL    /* FACI0 Base address */
#define R_RFD_BASE_ADDRESS_FACI2    0xFFA18000UL    /* FACI2 Base address */

/**********************************************************************************************************************
    Address of FACI command issue area
**********************************************************************************************************************/

#define R_RFD_CMDAREA_FACI0         0xFFA20000UL    /* FACI0 Command-issuing area */
#define R_RFD_CMDAREA_FACI2         0xFFA40000UL    /* FACI2 Command-issuing area */

/**********************************************************************************************************************
    Address of FHVE register
**********************************************************************************************************************/

#define R_RFD_REG_ADDRESS_FHVE3_0   0xFF984800UL    /* FHVE3FP0 register address (For FACI0)  */
#define R_RFD_REG_ADDRESS_FHVE15_0  0xFF984804UL    /* FHVE15FP0 register address (For FACI0) */

#define R_RFD_REG_ADDRESS_FHVE3_2   0xFF984820UL    /* FHVE3FP1 register address (For FACI2)  */
#define R_RFD_REG_ADDRESS_FHVE15_2  0xFF984824UL    /* FHVE15FP1 register address (For FACI2) */

/**********************************************************************************************************************
    For "Data flash" control setting
**********************************************************************************************************************/

/**********************************************************************************************************************
    Data Flash is controlled by RFD28F?
      - R_RFD_ENABLE  : Data Flash Memory is controlled by RFD28F
      - R_RFD_DISABLE : Data Flash Memory is not controlled by RFD28F
    
    If this definition is "R_RFD_DISABLE", APIs related Data Flash Memory are not executed.
**********************************************************************************************************************/

#define R_RFD_CONTROL_TARGET_DATAFLASH  R_RFD_ENABLE    /* Data Flash Memory is controlled by RFD28F or not */

/**********************************************************************************************************************
    Address of Data Flash area
**********************************************************************************************************************/

#define R_RFD_DF_BASE_FACI0         0xFF200000UL        /* Start address of Data Flash Memory (controlled by FACI0) */
#define R_RFD_DF_BASE_FACI1         R_RFD_NO_DEFINITION /* Start address of Data Flash Memory (controlled by FACI1) */
#define R_RFD_DF_BASE_FACI2         0xFF220000UL        /* Start address of Data Flash Memory (controlled by FACI2) */
#define R_RFD_DF_END                0xFF22FFFFUL        /* End address of Data Flash Memory                         */

/**********************************************************************************************************************
    For "Code flash" control setting
**********************************************************************************************************************/

/**********************************************************************************************************************
    Code Flash is controlled by RFD28F?
      - R_RFD_ENABLE  : Code Flash Memory is controlled by RFD28F
      - R_RFD_DISABLE : Code Flash Memory is not controlled by RFD28F
    
    If this definition is "R_RFD_DISABLE", APIs related Code Flash Memory are not executed.
**********************************************************************************************************************/

#define R_RFD_CONTROL_TARGET_CODEFLASH  R_RFD_ENABLE    /* Code Flash Memory is controlled by RFD28F or not */

/**********************************************************************************************************************
    MAP Mode
        - Single map mode : R_RFD_SINGLE
        - Double map mode : R_RFD_DOUBLE
**********************************************************************************************************************/

#define R_RFD_MAPMODE                   R_RFD_SINGLE    /* MAP mode */

/**********************************************************************************************************************
    Block Protection area1 is exist?
        - Exist     : R_RFD_ENABLE
        - Not exist : R_RFD_DISABLE
**********************************************************************************************************************/

#define R_RFD_BLOCK_PROTECTION_AREA1    R_RFD_DISABLE   /* Block Protection area1 is exist? */

/**********************************************************************************************************************
    FPMON check is enable?
        - Enable    : R_RFD_ENABLE
        - Disable   : R_RFD_DISABLE
**********************************************************************************************************************/

#define R_RFD_FPMON_CHECK               R_RFD_ENABLE    /* FPMON register check is valid or invalid */

/**********************************************************************************************************************
    Address of Code Flash area
**********************************************************************************************************************/

#define R_RFD_CF_BASE_FACI0         0x00000000UL        /* Start address of Code Flash Memory (controlled by FACI0) */
#define R_RFD_CF_BASE_FACI1         R_RFD_NO_DEFINITION /* Start address of Code Flash Memory (controlled by FACI1) */
#define R_RFD_CF_BASE_FACI2         R_RFD_NO_DEFINITION /* Start address of Code Flash Memory (controlled by FACI2) */
#define R_RFD_CF_END                0x005FFFFFUL        /* End address of Code Flash Memory                         */

/**********************************************************************************************************************
    Address of Data Flash ECC Control Register (For Read access)
**********************************************************************************************************************/

#define R_RFD_BASE_ADDRESS_DFECC    0xFFC62C00UL        /* Address of Data Flash ECC Controller                     */


#endif  /* defined(__RH850_U2B6__), defined(__RH850_U2B10__), else */


#endif  /* R_RFD_CONFIG_H */
