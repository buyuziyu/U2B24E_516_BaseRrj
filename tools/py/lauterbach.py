import os
from pathlib import Path

文件路径_setEntrance            = os.getcwd() + r'\tools\LauterbachScript\Lauterbach_SetEntrance.cmm'
文件路径_rh850_serialflashprog  = os.getcwd() + r'\tools\LauterbachScript\rh850_serialflashprog.cmm'

Value_劳特巴赫启动脚本 = [r'Start ',
                        r'\bin\windows64\t32mv800.exe -c ',
                        r'\my_config_usb.t32 -s ',
                        r'\tools\LauterbachScript\Lauterbach_SetEntrance.cmm']


def 接口_替换CMM脚本配置信息(工程名称, 芯片型号, 内核数量):

    try:
        # 修改 Lauterbach_SetEntrance.cmm #####################################################
        with open(文件路径_setEntrance, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        found = False
        for i, line in enumerate(lines):
            if "CORE.ASSIGN" in line:
                numbers = [str(i) for i in range(1, 内核数量 + 1)]
                lines[i] = "CORE.ASSIGN" + ' ' + " ".join(numbers)
                found = True
                print(f'  调整脚本 Lauterbach_SetEntrance.cmm 内核数量: {lines[i]}')
                lines[i] += '\n'
                # break

            if "Data.Load.Elf" in line:
                lines[i] = "Data.Load.Elf ./output/" + 工程名称 + ".elf /GHS /ALTBITFIELDS /RelPATH"
                found = True
                print(f'  调整脚本 Lauterbach_SetEntrance.cmm 调试ELF文件: {lines[i]}')
                lines[i] += '\n'
                break

        if found:
            with open(文件路径_setEntrance, 'w', encoding='utf-8') as f:
                f.writelines(lines)
        else:
            print(f"  Lauterbach_SetEntrance.cmm 中未找到包含目标配置行")


        # 修改 rh850_serialflashprog.cmm #####################################################
        with open(文件路径_rh850_serialflashprog, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        found = False
        for i, line in enumerate(lines):
            if "  SYStem.CPU " in line:
                lines[i] = "  SYStem.CPU " + 芯片型号
                found = True
                print(f'  调整脚本 rh850_serialflashprog.cmm  调试芯片型号: {lines[i]}')
                lines[i] += '\n'
                break

        if found:
            with open(文件路径_rh850_serialflashprog, 'w', encoding='utf-8') as f:
                f.writelines(lines)
        else:
            print(f"  rh850_serialflashprog.cmm 中未找到包含目标配置行")


    except FileNotFoundError:
        print(f"  替换CMM脚本配置信息错误：文件 '{文件路径_setEntrance}' 不存在")
    except PermissionError:
        print(f"  替换CMM脚本配置信息错误：没有权限访问文件 '{文件路径_setEntrance}'")
    except Exception as e:
        print(f"  替换CMM脚本配置信息文件时发生错误：{e}")


def 接口_重建劳特巴赫脚本(文件路径_Lauterbach根目录):
    file_path = os.getcwd() + r"\Startup_Lauterbach.bat"

    try:
        with open(file_path, 'w', encoding='utf-8') as file:
            bat_content = Value_劳特巴赫启动脚本[0] + 文件路径_Lauterbach根目录 + Value_劳特巴赫启动脚本[1] + 文件路径_Lauterbach根目录 + Value_劳特巴赫启动脚本[2] + os.getcwd() + Value_劳特巴赫启动脚本[3]
            file.write(bat_content)
            print(f'  构建劳特巴赫启动脚本: {bat_content}')
    except PermissionError:
        print(f"  构建劳特巴赫启动脚本错误：没有权限访问文件 {file_path}")
    except Exception as e:
        print(f"  构建劳特巴赫启动脚本文件时发生错误：{e}")