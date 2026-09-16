import os

# 目标匹配字符串
target_str = "#pragma ghs section"
# 获取当前脚本所在目录
current_path = os.getcwd()

# 遍历当前路径下所有文件（不包含子文件夹）
for filename in os.listdir(current_path):
    file_full_path = os.path.join(current_path, filename)
    # 只处理文件，跳过文件夹
    if os.path.isfile(file_full_path):
        try:
            # 以utf-8编码读取，出错则跳过该文件
            with open(file_full_path, "r", encoding="utf-8") as f:
                line_num = 1
                for line in f:
                    if target_str in line:
                        # 打印文件名、行号、匹配行
                        print(f"【文件】{filename} 第{line_num}行：{line.rstrip()}")
                    line_num += 1
        except UnicodeDecodeError:
            # 二进制文件/非文本文件编码错误，跳过
            print(f"跳过非文本文件：{filename}（编码读取失败）")
        except Exception as e:
            print(f"读取文件 {filename} 异常：{str(e)}")