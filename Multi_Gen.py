# -*- coding: utf-8 -*-
# Auther:Loki
# Email:liaoyy@etouch.net.cn
# Data:2025/03/11
# Content:2025/03/06    1.识别文件增加asm后缀
# Content:2025/04/09    1.增加输出地址不做限制的HEX
# Content:2025/06/13    1.封装忽略改为U2x所有封装
#                       2.外部脚本 - 允许脚本根据芯片型号变更OPBT15 for U2C(删除)
# Content:2025/07/15    1.根据型号初始化OPBT
# Content:2025/07/22    1.变更工程结构
# Content:2025/07/30    1.区分单双核工程
# Content:2025/08/07	1.增加移植MCAL功能
# Content:2025/12/03    1.增加劳特巴赫相关内容
# Content:2025/12/15    1.增加R431版本MCAL多实例工程创建
# Content:2026/01/15    1.调整 接口_替换CMM脚本配置信息 修改项
#                       2.增加输出信息
# Content:2026/03/02    1.增加 frame pointer 配置项
# Content:2026/06/09    1.增加 根据 MCU_SERIES 选择 ld文件
# Content:2026/07/13    1.内核变更为大小核组合

import os
import sys
from sys import path
from pathlib import Path
import time

from tools.py.CSA_850               import set_CSA
from tools.py.MCAL                  import get_MCAL_files
from tools.py.lauterbach            import 接口_替换CMM脚本配置信息
from tools.py.lauterbach            import 接口_重建劳特巴赫脚本
from tools.py.creat_ghs_prj         import 接口_编译工程
from tools.py.creat_ghs_prj         import 接口_创建编译脚本
from tools.py.R431_MultiInstance    import 接口_多实例工程修改
from tools.py.select_ld             import clean_gpj_link_files    

# 根据芯片和工程修改<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
PROGRAM             = "U2B24-E_25BNFABC"
MCU_SERIES          = "U2B24-E"               # 芯片型号
PACKAGE             = "516"                 # 管脚数量
PRODUCTION          = "R7F7025BNFABC"
MAIN_CORE_ARCH      = "rh850g4mh"           # 主核类型
MAIN_CORE_NUM       = 6                     # 主核数量
SUB_CORE_ARCH       = "rh850g4kh"           # 小核类型
SUB_CORE_NUM        = 1                     # 小核数量
MAP_MODE            = "SM"                  # SM - Single Map, DM - Double Map, 先切换OPBT12模式配置刷了芯片再更新工程

SET_CSA_OPBT                = 'OFF'                 # 使能脚本根据芯片型号更新OPBT
SET_MCAL_PRJ                = 'OFF'                 # 删除 R_MCAL 重新移植MCAL文件
SET_GHS_PRJ_BUILD           = 'OFF'                 # 创建工程后编译
SET_MUL_INST                = 'OFF'                 # 按照多实例要求修改工程 该功能仅适用于U2A U431版本MCAL
SET_LAUTERBACH_ENABLE       = 'OFF'                 # 使能劳特巴赫相关功能


文件路径_MCAL根目录        = r'C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03'
文件路径_GHS根目录         = r"C:\ghs\comp_202514"
文件路径_Lauterbach根目录  = r"C:\T32"
文件路径_工程根目录        = os.getcwd()

# 全局宏定义
GLOBALDEFINE        = [ "__RH850_" + MCU_SERIES[:3] + "__",
                        "__RH850_" + MCU_SERIES + "__",
                        "MAX_PE6",
                        "PE0_USED",
                        "PE1_USED",
                        "PE2_USED",
                        "PE3_USED",
                        "PE4_USED",
                        "PE5_USED",
                        "PE6_USED",
                    ]
# 忽略文件夹
IGNORE_DIR          = [ ".git",
                        "tools",
                        "py",
                        "BIN",
                        "OBJ",
                        "tools",
                        ".vscode", 
                        "output",
                        "sample",
                        "开发信息",
                        "trash",
                        "flash",
                        "flsdrv_hex",
                        "ccrh",
                        "iar",
                        "ghslib",
						'U2B6',

						# 未启用模块
                        "SampleCode",
                        'Fr',       'fr',       'fr_output',
                        'RamTst',   'ramtst',   'ramtst_output',
                        'Ocu',      'ocu',      'ocu_output',
						
                        # 使用MCAL时不使用RDF28F库
                        'RFD28F',
                        'RFD28',

                        # flash库文件有冲突，需要使用时再编译进去
                        'Mem',      'mem',      'mem_output',
                        'MemAcc',   'memacc',   'memacc_output',
                        'Fee',      'fee',      'fee_output',
						'FlsTst',   'flstst',   'flstst_output',
                        'Fls',      'fls',      'fls_output',
                        
                    ]
# 忽略文件名，格式：文件名.后缀 或者 部分文件名
IGNORE_FILES        = [ "r_cg_main.c",      # smc main文件
                        "r_cg_cgc.c",
                        "r_cg_systeminit.c",
                        "_59_INST",         # MCAL多实例
                        "_59_Inst",         # MCAL多实例
                        "r_cg_intvector_",  # SMC的中断向量表
                        "r_smc_intprg.c",   # SMC的中断向量表
                        "r_smc_interrupt.c",# SMC的中断向量表
                        "ignore_",          # SMC配置的观察模块
                        ".py",              # py脚本
                        "tools",            # 编译器
                        ".readme",

                    ]

多实例模块          = ['can', 'Can', 'CAN']

# 根据芯片型号选择的ld文件，把除了U2A16/8/6以外的ld文件放在编译文件里
额外保留Link        = ["xxx.ld"]

# 根据芯片和工程修改>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

# 把静态代码里非本封装的文件夹添加到忽略列表中，该列表为U2X所有封装
PORT_IGNORE_DIR = [ "U2A6_BGA144",  "U2A6_BGA156",  "U2A6_BGA176",  "U2A6_BGA292",
                    "U2A8_BGA292",  "U2A8_BGA373",
                    "U2A16_BGA292", "U2A16_BGA373", "U2A16_BGA516",
    
                    "U2B6_BGA292",
                    "U2B10_BGA292", "U2B10_BGA373", "U2B10_BGA468",

                    "U2B6-E_BGA292",
                    "U2B12-E_BGA292", "U2B12-E_BGA516",
                    "U2B24-E_BGA292", "U2B24-E_BGA516",
                    
                    "U2C2_BGA100",  "U2C2_BGA144",
                    "U2C4_BGA100",  "U2C4_BGA144",  "U2C4_BGA292",
                    "U2C8_BGA292"
                    ]

PRJ_TARGET          = "Startup"
PROG_TARGET         = "cfg_build_option"
MC_CFG              = "cfg_multi_core_file"
SOURCE_FILE         = "cfg_build_files"
OUTPUT_DIR          = "output"

PRJ_FILE_SUFFIX     = ".gpj"
SRC_FILE_SUFFIX     = ".c"
GHS_850_FILE_SUFFIX = ".850"
ASM_FILE_SUFFIX     = ".asm"
LIB_FILE_SUFFIX     = ".a"
LD_FILE_SUFFIX      = ".ld"
INC_FILE_SUFFIX     = ".h"
GHSMC_FILE_SUFFIX   = ".ghsmc"
PROJ_FILE_TYPE      = [ SRC_FILE_SUFFIX,\
                        ASM_FILE_SUFFIX,\
                        LIB_FILE_SUFFIX,\
                        LD_FILE_SUFFIX,\
                        GHS_850_FILE_SUFFIX,\
                        INC_FILE_SUFFIX]

DIR_SPILT_SYMBOL_TO_WRITE = '\\'
INC_HEADER          = "\t-I..\\..\\"
NEW_LINE_DEF        = "\n"
PRJ_FILE_HEADER     = "#!gbuild\n"
DIR_SPLIT_SYMBOL    = '/'


# startup.ghsmc****************************************************start
PRJ_COMPILER_OPTION = [\
"\
primaryTarget=v800_standalone.tgt\n\
[Project]\n\
\t{optgroup=GhsCompilerOptions}\n\
\t-cpu=" + MAIN_CORE_ARCH + "\n\
\t-ffunctions\n\
\t-fhard\n\
\t--preprocess_linker_directive_full\n",\
"\
\t-ghsmc_file=.\\tools\\ghs\\" + MC_CFG + GHSMC_FILE_SUFFIX + "\n",\
"\
\t-object_dir=" + OUTPUT_DIR + "\n" + \
".\\tools\\ghs\\" + PROG_TARGET + PRJ_FILE_SUFFIX + "\t[Program]\n"\
]
# startup.ghsmc----------------------------------------------------end


# cfg_build_option.ghsmc****************************************************start
PROGRAM_COMPILER_OPTION = \
"\
[Program]\n\
\t-object_dir=OBJ\n\
\t-Omaxdebug\n\
\t-gtws\n\
\t-ga\n\
\t-G\n\
\t-gsize\n\
\t-farcalls\n\
\t-ghsmc_core_count=" + str(MAIN_CORE_NUM + SUB_CORE_NUM) + "\n\
\t-ignore_debug_references\n\
\t-locatedprogram\n\
\t-fnofunctions\n\
\t-dwarf2\n\
\t-paddr_offset=0\n\
\t-shorten_loads\n\
\t-no_init_ram_at_startup\n\
\t-memory\n\
\t{optgroup=GhsCommonOptions} -o ./" + OUTPUT_DIR + "/" + PROGRAM + ".elf" + "\n\
\t-object_dir=" + OUTPUT_DIR + "\\objs\n\
\t:postexec='gsrec -fill_gap 0xFF -e 0 -hex386 "+ OUTPUT_DIR + "/" + PROGRAM + ".elf -o "+ OUTPUT_DIR +"/" + "AllAddr.hex'\n\
\t:postexec='gsrec -fill_gap 0xFF -e 0 -start 0xFF321000 -hex386 "+ OUTPUT_DIR + "/" + PROGRAM + ".elf -o "+ OUTPUT_DIR +"/" + "OPBT.hex'\n\
\t:postexec='gsrec -fill_gap 0xFF -e 0 -end 0x02000000 -hex386 "+ OUTPUT_DIR + "/" + PROGRAM + ".elf -o "+ OUTPUT_DIR +"/" + PROGRAM + ".hex'\n\
\t:postexec='gsrec -fill_gap 0xFF -e 0 -end 0x02000000 -S3 "    + OUTPUT_DIR + "/" + PROGRAM + ".elf -o "+ OUTPUT_DIR +"/" + PROGRAM + ".s19'\n\
\t:postexec='gsrec -e 0 -noS5 "+ OUTPUT_DIR + "/" + PROGRAM + ".elf -o output/" + PROGRAM + ".srec'\n\
\n"

SUB_PRJ_COMPILER_OPTION = "[Subproject]\n"
SUB_PRJ_COMPILER_FILES = SOURCE_FILE+".gpj\n"
# cfg_build_option.ghsmc----------------------------------------------------end


# cfg_multi_core_file.ghsmc****************************************************start
PROGRAM_GHSMC_HEADER = \
"\
version = 1\n\
title = \"My Target\"\n\
\n\
core {\n\
"

PROGRAM_GHSMC_DOENLOAD = \
"\
\t0 { download = {\"../../" + OUTPUT_DIR + "/" + PROGRAM + ".elf" + "\"} }\n\
"

PROGRAM_GHSMC_SYMBOL = \
"\
 { symbol = {\"../../" + OUTPUT_DIR + "/" + PROGRAM + ".elf" + "\"} }\n\
"

PROGRAM_GHSMC_TAIL = \
"\
}\n\
"
# cfg_multi_core_file.ghsmc----------------------------------------------------end


# 构建工程编译配置文件cfg_build_option.gpj
def add_build_option(cur_dir):

    os.makedirs(os.path.dirname(cur_dir + "\\tools\\ghs\\" + PROG_TARGET + PRJ_FILE_SUFFIX), exist_ok=True)
    project_file = open(cur_dir + "\\tools\\ghs\\" + PROG_TARGET + PRJ_FILE_SUFFIX, 'w')
    project_file.write(PRJ_FILE_HEADER)
    project_file.write(PROGRAM_COMPILER_OPTION)
    # 添加库文件路径
    # f_root是当前文件夹的绝对路径，f_dirs是当前文件夹下的子文件夹列表，f_files是当前文件夹下的文件列表
    for f_root, f_dirs, f_files in os.walk(cur_dir):
        relative_path = os.path.relpath(os.path.join(f_root))

        # 拆分路径上所有文件夹名字
        dir_lists = relative_path.split(DIR_SPILT_SYMBOL_TO_WRITE)

        # Case.1 当前文件夹在忽略文件加列表里 - pass
        ignore_file = [s for s in dir_lists if s in IGNORE_DIR]
        if ignore_file:
            pass
        # Case.2 当前文件夹路径下子文件包含库文件(.h)，把当前路径放入配置文件
        else:
            isIncludeLibraryFiles = False
            for file in f_files:
                file_extension = os.path.splitext(file)[1]
                if file_extension == ".h":
                    isIncludeLibraryFiles = True
            if isIncludeLibraryFiles == True:
                project_file.write(INC_HEADER + os.path.relpath(os.path.join(f_root)) + NEW_LINE_DEF)

    project_file.write(SUB_PRJ_COMPILER_FILES)
    project_file.close()

# 构建代码文件包含工程cfg_build_files.gpj
def add_src_file(cur_dir):

    os.makedirs(os.path.dirname(cur_dir + "\\tools\\ghs\\" + SOURCE_FILE + PRJ_FILE_SUFFIX), exist_ok=True)
    project_file = open(cur_dir + "\\tools\\ghs\\" + SOURCE_FILE + PRJ_FILE_SUFFIX, 'w')
    project_file.write(PRJ_FILE_HEADER)
    project_file.write(SUB_PRJ_COMPILER_OPTION)

    # 获取当前目录的绝对路径
    prj_path = cur_dir
    
    # 递归遍历文件夹及其子文件夹
    for f_root, f_dirs, f_files in os.walk(cur_dir):
        for file_name in f_files:
            # 判断文件是否在忽略列表内
            if file_name in IGNORE_FILES:
                pass
            else:
                # 构建文件的完整路径
                file_path = os.path.join(f_root, file_name)
                # 输出文件的路径以相对于当前目录的路径开始
                relative_path = os.path.relpath(file_path, prj_path)
                # 拆分路径上所有文件夹名字
                dir_lists = relative_path.split(DIR_SPILT_SYMBOL_TO_WRITE)
                # 判断路径上是否存在文件夹是不需要的
                ignore_file_1 = [s for s in dir_lists if s in IGNORE_DIR]
                ignore_file_2 = [s for s in dir_lists if any(item in s for item in IGNORE_FILES)]
                if ignore_file_1 or ignore_file_2:
                    pass
                else:
                    # 判断后缀
                    cur_file_suffix = os.path.splitext(relative_path)[1]
                    if cur_file_suffix in PROJ_FILE_TYPE:
                        # 添加需要编译的文件
                        project_file.write("..\\..\\" + relative_path + NEW_LINE_DEF)
    project_file.close()


def Project_Generator():
    global IGNORE_DIR

    # 1.构建Startup.gpj
    print('\n构建Startup.gpj*************************************************************************')
    project_file = open(os.getcwd() + DIR_SPLIT_SYMBOL + PRJ_TARGET + PRJ_FILE_SUFFIX, 'w')
    project_file.write(PRJ_FILE_HEADER)
    project_file.write(PRJ_COMPILER_OPTION[0])
    if (MAIN_CORE_NUM + SUB_CORE_NUM) > 1:
        project_file.write(PRJ_COMPILER_OPTION[1])
    project_file.write(PRJ_COMPILER_OPTION[2])

    for item in GLOBALDEFINE:
        project_file.write("\t-D" + item.replace('-', '') + "\n")
    project_file.close()

    remove_target = MCU_SERIES + "_BGA" + PACKAGE
    for item in PORT_IGNORE_DIR:
        if remove_target == item:
            PORT_IGNORE_DIR.remove(remove_target)
    IGNORE_DIR.extend(PORT_IGNORE_DIR)

    # 2.构建构建cfg_build_option.gpj
    print('\n构建cfg_build_option.gpj****************************************************************')
    add_build_option(os.getcwd())

    # 3.构建cfg_build_files.gpj
    print('\n构建cfg_build_files.gpj*****************************************************************')
    add_src_file(os.getcwd())
    clean_gpj_link_files(MCU_SERIES, MAP_MODE)

    # 4.构建cfg_multi_core_file.ghsmc工程文件
    print('\n构建cfg_multi_core_file.gpj*************************************************************')
    if (MAIN_CORE_NUM + SUB_CORE_NUM) > 1:
        project_file = open(os.getcwd() + "/tools/ghs/" + DIR_SPLIT_SYMBOL + MC_CFG + GHSMC_FILE_SUFFIX, 'w')    
        project_file.write(PROGRAM_GHSMC_HEADER)
        project_file.write(PROGRAM_GHSMC_DOENLOAD)
        for i in range(1,MAIN_CORE_NUM + SUB_CORE_NUM):
            project_file.write("\t")
            PROGRAM_GHSMC_SYMBOL_NEW = str(i) + PROGRAM_GHSMC_SYMBOL
            project_file.write(PROGRAM_GHSMC_SYMBOL_NEW)
        project_file.write(PROGRAM_GHSMC_TAIL)
        
        project_file.close()




def ExtendedFunction():

    if SET_CSA_OPBT == 'ON':
        print('\n更新CSA文件****************************************************************************')
        set_CSA(MCU_SERIES)
        print("  CSA文件更新完成")

    if SET_MCAL_PRJ == 'ON':
        print('\n更新MCAL文件***************************************************************************')
        get_MCAL_files(文件路径_MCAL根目录, 文件路径_工程根目录)
        print("  MCAL文件更新完成")

    if SET_MUL_INST == 'ON':
        接口_多实例工程修改(多实例模块)

    if SET_LAUTERBACH_ENABLE == 'ON':
        print('\n接口_替换CMM脚本配置信息****************************************************************')
        接口_替换CMM脚本配置信息(PROGRAM, PRODUCTION, MAIN_CORE_NUM + SUB_CORE_NUM)

        print('\n接口_重建劳特巴赫脚本*******************************************************************')
        接口_重建劳特巴赫脚本(文件路径_Lauterbach根目录)

    print('\n接口_创建编译脚本***********************************************************************')
    接口_创建编译脚本(文件路径_GHS根目录)

    if SET_GHS_PRJ_BUILD == 'ON':
        print('\n接口_编译工程***************************************************************************')
        接口_编译工程(文件路径_GHS根目录)
        print(r'工程编译结束，完整编译日志见 .\output\buila_log.txt')

Project_Generator()

ExtendedFunction()

print('\n****************************************************************************************')
print(PROGRAM + ' 工程创建任务已结束, 若创建失败, 请联系 liaoyy@etouch.net.cn')
input("\n按 Enter 键继续...")

