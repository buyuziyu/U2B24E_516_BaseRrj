# -*- coding: utf-8 -*-
"""
chaoyang.ren.aj@renesas.com
"""

import os

MOD_NAME = "delay"

NEWLINE = "\n"

FILE_HEADER = \
'''
/******************************************************************************* 
* DISCLAIMER 
* This software is supplied by Renesas Electronics Corporation and is only  
* intended for use with Renesas products. No other uses are authorized. This  
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE  
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. 
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS  
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software, 
* you agree to the additional terms and conditions found by accessing the  
* following link: 
* http://www.renesas.com/disclaimer 
* 
* Copyright (C) 2012, 2014 Renesas Electronics Corporation. All rights reserved.     
*******************************************************************************/'''
INC_ANNOTATION = \
'''
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/'''
MICRO_ANNOTATION = \
'''
/*****************************************************************************
 Macro definitions
 *****************************************************************************/'''
TYPEDEF_ANNOTATION = \
'''
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/'''
GLOBAL_VAR_ANNOTATION = \
'''
/*****************************************************************************
 Global variables
 *****************************************************************************/'''
STATIC_VAR_ANNOTATION = \
'''
/*****************************************************************************
 Global static variables
 *****************************************************************************/'''
GLOBAL_FUN_ANNOTATION = \
'''
/*****************************************************************************
 Global functions
 *****************************************************************************/'''
STATIC_FUN_ANNOTATION = \
'''
/*****************************************************************************
 Static functions
 *****************************************************************************/'''
GLOBAL_FUN_HEADER_ANNOTATION = \
'''
/*****************************************************************************
--------------------- Global functions --------------------------------------
 *****************************************************************************/'''
STATIC_FUN_HEADER_ANNOTATION = \
'''
/*****************************************************************************
--------------------- Static functions --------------------------------------
 *****************************************************************************/'''
FUNCTION_HEADER_ANNOTATION = \
'''
/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/'''

C_INC = "#include \"r_" + MOD_NAME + ".h\"" + NEWLINE + "#include \"r_" + MOD_NAME + "_reg.h\""
H_INC = "#include \"r_compiler.h\""

PRE_INC_MICRO_S = "#ifndef R_" + MOD_NAME.upper() + "_H" + NEWLINE + "#define R_" +  MOD_NAME.upper() + "_H"
PRE_INC_MICRO_E = "#endif  /* R_" + MOD_NAME.upper() + "_H */"
PRE_INC_REG_MICRO_S = "#ifndef R_" + MOD_NAME.upper() + "_REG_H" + NEWLINE + "#define R_" +  MOD_NAME.upper() + "_REG_H"
PRE_INC_REG_MICRO_E = "#endif  /* R_" + MOD_NAME.upper() + "_REG_H */"

mod_c_file = open("r_" + MOD_NAME + ".c", 'w')
mod_c_file.write(FILE_HEADER)
mod_c_file.write(NEWLINE)
mod_c_file.write(INC_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.write(C_INC)
mod_c_file.write(NEWLINE)
mod_c_file.write(MICRO_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.write(TYPEDEF_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.write(GLOBAL_VAR_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.write(STATIC_VAR_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.write(STATIC_FUN_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.write(GLOBAL_FUN_HEADER_ANNOTATION)
mod_c_file.write(FUNCTION_HEADER_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.write(STATIC_FUN_HEADER_ANNOTATION)
mod_c_file.write(NEWLINE)
mod_c_file.close()

mod_h_file = open("r_" + MOD_NAME + ".h", 'w')
mod_h_file.write(FILE_HEADER)
mod_h_file.write(NEWLINE)
mod_h_file.write(PRE_INC_MICRO_S)
mod_h_file.write(NEWLINE)
mod_h_file.write(INC_ANNOTATION)
mod_h_file.write(NEWLINE)
mod_h_file.write(H_INC)
mod_h_file.write(NEWLINE)
mod_h_file.write(MICRO_ANNOTATION)
mod_h_file.write(NEWLINE)
mod_h_file.write(TYPEDEF_ANNOTATION)
mod_h_file.write(NEWLINE)
mod_h_file.write(GLOBAL_VAR_ANNOTATION)
mod_h_file.write(NEWLINE)
mod_h_file.write(GLOBAL_FUN_ANNOTATION)
mod_h_file.write(NEWLINE)
mod_h_file.write(NEWLINE)
mod_h_file.write(PRE_INC_MICRO_E)
mod_h_file.close()

mod_h_reg_file = open("r_" + MOD_NAME + "_reg.h", 'w')
mod_h_reg_file.write(FILE_HEADER)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(PRE_INC_REG_MICRO_S)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(INC_ANNOTATION)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(H_INC)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(MICRO_ANNOTATION)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(TYPEDEF_ANNOTATION)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(GLOBAL_VAR_ANNOTATION)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(GLOBAL_FUN_ANNOTATION)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.write(PRE_INC_REG_MICRO_E)
mod_h_reg_file.write(NEWLINE)
mod_h_reg_file.close()