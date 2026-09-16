import os

def clean_gpj_link_files(芯片型号, 存储模式):
    """
    清理cfg_build_files.gpj文件中不需要的链接脚本文件(.ld)
    保留规则：
    1. 文件名等于芯片型号变量值的.ld文件
    2. 额外保留Link列表中指定的.ld文件
    3. 所有非.ld后缀的文件全部保留
    """
    # ==================== 配置区域 - 请根据实际情况修改 ====================
    # cfg_build_files.gpj文件的路径
    GPJ_FILE_PATH = os.getcwd() + r"\tools\ghs\cfg_build_files.gpj"
    
    # 额外保留的链接脚本文件列表
    额外保留Link = ["xxx.ld"]
    
    # =====================================================================

    # 检查文件是否存在
    if not os.path.exists(GPJ_FILE_PATH):
        print(f"  错误：文件 {GPJ_FILE_PATH} 不存在！")
        return False

    try:
        # 读取文件所有行
        with open(GPJ_FILE_PATH, "r", encoding="utf-8") as f:
            lines = f.readlines()

        original_line_count = len(lines)
        filtered_lines = []
        deleted_lines = []

        # 处理每一行
        for line in lines:
            # 去除首尾空白字符，但保留原始换行符
            stripped_line = line.strip()
            
            # 跳过空行
            if not stripped_line:
                filtered_lines.append(line)
                continue

            # 检查是否是.ld后缀的链接脚本文件
            if stripped_line.lower().endswith(".ld"):
                # 提取文件名（不含路径和后缀）
                LD文件全名 = os.path.basename(stripped_line)
                LD文件名 = os.path.splitext(LD文件全名)[0]

                # 删除U2Bx-E的'-'
                芯片型号 = 芯片型号.replace('-', '')
                
                # 判断是否需要保留
                if 芯片型号+'_'+存储模式 == LD文件名:
                    # 匹配MCU系列名称和存储模式，保留
                    filtered_lines.append(line)
                elif LD文件全名 in 额外保留Link:
                    # 在额外保留列表中，保留
                    filtered_lines.append(line)
                else:
                    # 不符合保留条件，删除该行
                    deleted_lines.append(stripped_line)
            else:
                # 非.ld文件，全部保留
                filtered_lines.append(line)

        # 将处理后的内容写回文件
        with open(GPJ_FILE_PATH, "w", encoding="utf-8") as f:
            f.writelines(filtered_lines)
        
        if deleted_lines:
            print("  从cfg_build_files.gpj中移除的链接脚本文件：")
            for file in deleted_lines:
                print(f"    {file}")
        else:
            print("  没有需要删除的链接脚本文件")

        return True

    except Exception as e:
        print(f"  处理过程中发生错误：{str(e)}")
        return False