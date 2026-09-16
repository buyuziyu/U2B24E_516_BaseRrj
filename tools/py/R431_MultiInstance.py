import os
from pathlib import Path



def 接口_多实例工程修改(目标模块):

    当前目录                = os.getcwd()

    目标cfg_build_files     = 当前目录 + r'\tools\ghs\cfg_build_files.gpj'
    目标cfg_build_option    = 当前目录 + r'\tools\ghs\cfg_build_option.gpj'

    临时cfg_build_files     = 当前目录 + r'\tools\ghs\cfg_build_files.txt'
    临时cfg_build_option    = 当前目录 + r'\tools\ghs\cfg_build_option.txt'

    MCLA静态代码路径         = 当前目录 + r'\code\R_MCAL\modules\StaticCode'

    字典_MCAL静态代码文件夹路径 = {}

    # 替换 cfg_build_files.gpj 的内容********************************************************************************************
    with open(目标cfg_build_files, 'r') as f_in, open(临时cfg_build_files, 'w') as f_out:
        for line in f_in:
            # 去除行尾换行符后拆分
            parts = line.strip().split('\\')  
            # 用正斜杠拼接
            new_line = '\\'.join(parts)
            # 目标模块 仅保留内多实例文件
            for 模块 in 目标模块:
                if ('src' in parts) and ('59_Inst' not in new_line) and (模块 in parts):
                    new_line = '#' + new_line

            # # 非目标模块 屏蔽多实例文件
            # if ('src' in parts) and ('59_Inst' in new_line) and ('_output' not in new_line) and ([x for x in parts if x in 目标模块] == []):
            #     new_line = '#' + new_line

            if ('59_Inst' in new_line) and ('_output' not in new_line) and (not any(word in new_line for word in 目标模块)):
                new_line = '#' + new_line

            # print(str([x for x in parts if x in 目标模块])+ '  ' + line)

            # 写入新文件并保留换行
            f_out.write(new_line + '\n')
    f_in.close()
    f_out.close()


    # 替换 cfg_build_option.gpj 的内容********************************************************************************************
    # 步骤1：获取静态代码所有模块文件夹的路径
    root = Path(MCLA静态代码路径)
    try:
        # 遍历根目录下的所有直接子文件夹
        for item in root.iterdir():
            if item.is_dir():
                folder_name = item.name
                
                # 获取该文件夹下的所有子文件夹（递归）
                subfolders = []
                
                # 使用rglob递归查找所有子文件夹
                for subfolder in item.rglob("*"):
                    if subfolder.is_dir() and subfolder != item:  # 排除自身
                        # 计算相对于根目录的相对路径
                        relative_path = subfolder.relative_to(root)
                        subfolders.append(r'	-I..\..\code\R_MCAL\modules\StaticCode' + '\\' + str(relative_path))
                
                # 按路径排序
                subfolders.sort()
                
                字典_MCAL静态代码文件夹路径[folder_name] = subfolders
                
    except PermissionError:
        print(f"  接口_多实例工程修改 无法访问路径 '{MCLA静态代码路径}' 下的某些文件夹")
    except Exception as e:
        print(f"  发生错误：{e}")

    # 步骤2：处理文件内容（删除包含目标模块的行）
    with open(目标cfg_build_option, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    保留行 = []
    替换标志 = ''
    for line in lines:
        # 使用反斜杠拆分（注意转义）
        parts = line.strip().split('\\')
        # 检查是否包含任意目标模块
        if "-I.." in line and any(module in parts for module in 目标模块):
            for part in parts:
                if part in 目标模块:
                    替换标志 = part
                    continue
            continue
        if 替换标志 != '':
            for newLibrary in 字典_MCAL静态代码文件夹路径[替换标志]:
                保留行.append(newLibrary + '\n')
                替换标志 = ''
        保留行.append(line)

    # 步骤3：写入最终文件（覆盖原文件）
    with open(临时cfg_build_option, 'w', encoding='utf-8') as f:
        f.writelines(保留行)
    f.close()

    os.replace(临时cfg_build_files,     目标cfg_build_files)
    os.replace(临时cfg_build_option,    目标cfg_build_option)

