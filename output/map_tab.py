import re
import os

def convert_spaces_to_tab(input_path, output_path=None):
    """
    将文件中的连续空格替换为一个制表符并另存为新文件
    :param input_path: 输入文件路径
    :param output_path: 输出文件路径（默认在输入文件名后添加 '_tabbed'）
    """
    # 设置默认输出路径
    if output_path is None:
        base, ext = os.path.splitext(input_path)
        output_path = f"{base}_tabbed{ext}"

    try:
        # 读取原文件内容
        with open(input_path, 'r', encoding='utf-8') as infile:
            content = infile.read()
        
        # 正则替换：所有连续空格 → 单个制表符
        modified_content = re.sub(r' +', '\t', content)  # 匹配1个或多个空格[9,10](@ref)
        
        # 写入新文件
        with open(output_path, 'w', encoding='utf-8') as outfile:
            outfile.write(modified_content)
        
        return f"处理完成！新文件已保存至: {os.path.abspath(output_path)}"
    
    except FileNotFoundError:
        return f"错误：文件不存在 - {input_path}"
    except Exception as e:
        return f"处理失败: {str(e)}"

# 使用示例
if __name__ == "__main__":
    input_file = "U2B10_254EFABG.map"  # 替换为实际文件路径
    result = convert_spaces_to_tab(input_file)
    print(result)